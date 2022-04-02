#include "bit_lab_utils.h"
#include "err.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define A_VAL (uint64_t)10
#define B_VAL (uint64_t)11
#define C_VAL (uint64_t)12
#define D_VAL (uint64_t)13
#define E_VAL (uint64_t)14
#define F_VAL 		(uint64_t)15
#define HEX_ERROR 	(uint64_t)17

#define BIAS 		(uint64_t)63
#define NUM_4_BIT_SUBCELLS 16
#define HEX_CELL	(uint64_t)4

// Postions defined as on Moodle
#define A_POS 0
#define B_POS 1
#define M_POS 2
#define R_POS 3
#define S_POS 4
#define NUM_COEFF 5
#define R_BASE 10
#define UINT32_SHIFT 32

uint64_t return_hex_val(char sign) {
	if (sign == 'A' || sign == 'a') return A_VAL;
	else if (sign == 'B' || sign == 'b') return B_VAL;
	else if (sign == 'C' || sign == 'c') return C_VAL;
	else if (sign == 'D' || sign == 'd') return D_VAL;
	else if (sign == 'E' || sign == 'e') return E_VAL;
	else if (sign == 'F' || sign == 'f') return F_VAL;
	else if (isdigit(sign)) return (uint64_t)(sign - '0');
	else return HEX_ERROR;
}

Bitmap* create_bitmap(size_t length) {
	size_t cell_number = DIV_64(length + BIAS); // Roundup - length at least 1
    // Added one for safety
    uint64_t* bit_array = calloc(cell_number + 1, sizeof(uint64_t));

    if (!bit_array) {
        print_error(ERR_0);
        exit(1);
    }

	Bitmap* result = malloc(sizeof(Bitmap));
	result->length = cell_number;
	result->array = bit_array;

	return result;
}

// Beginning from the end of the char array, we write from the beginning
// of the bit array - in 64-bit cells in form of unit64_t of the constant width.
Bitmap* convert_hex_to_bitmap(char* hex, size_t hex_length,
                              uint64_t labyrinth_size) {
	uint64_t hex_index = hex_length - 1;

    while (isspace(hex[hex_index]) && hex[hex_index] != 'x') {
        hex_index--;
    }

	if (hex[hex_index] == 'x') {
        return NULL;
	}

    // The values are stored by parts in 64-bit cells in form of uint64_t.
    // Since conversion from hexadecimal to binary consists of writing
    // the adjacent hexadecimal signs as four-bit blocks,
    // after conversion from hex the blocks are right shifted according to
    // the number of the section (one of the 16 sections, since 16*4 = 64)
    // and merged with the resulting cell using OR.
	uint64_t hex_converted;
	uint64_t shift;
	int bit_quartet;
	uint64_t cell = 0;
    bool read_at_least_one = false;

	Bitmap* converted = create_bitmap(labyrinth_size);
    uint64_t modulo = MOD_64(labyrinth_size);

	while (cell < converted->length) {
		shift = 0;
		bit_quartet = 0;
		while (bit_quartet < NUM_4_BIT_SUBCELLS) {
			if (hex[hex_index] == 'x') break;

			hex_converted = return_hex_val(hex[hex_index--]);
			if (hex_converted == HEX_ERROR) {
				delete_bitmap(converted);

                return NULL;
			}

            uint64_t shifted_by_4 = (hex_converted << shift);

            if (cell == converted->length - 1 && modulo != 0) {
                if ((shifted_by_4 >> modulo) != 0) {
                    delete_bitmap(converted);
                    return NULL;
                }
            }

            converted->array[cell] |= shifted_by_4;
			shift += 4;
			bit_quartet++;

            // Whether at least one number has been read
            if (!read_at_least_one) {
                read_at_least_one = true;
            }
		}

		if (hex[hex_index] != 'x') cell++;
		else break;
	}

    if (!read_at_least_one) {
        delete_bitmap(converted);
        return NULL;
    }

    // After filling the cells, there can be still unrecognized signs
    // (incorrect).
	if (cell == converted->length) {
		bool not_finished = true;
		while (not_finished) {
			while (isspace(hex[hex_index])) hex_index--;

			if (hex[hex_index] == 'x') {
				not_finished = false;
			}
			else if (hex[hex_index] != '0') {
				delete_bitmap(converted);

                return NULL;
			}
		}
	}

	return converted;
}


// Bitshift to the indicated position, after omitting appropriate number
// of full cells.
void set_bit(Bitmap* bit_array, uint64_t index) {
	bit_array->array[DIV_64(index)] |= ((uint64_t)1 << (index));
}

bool is_filled_cell(Bitmap* bit_array, uint64_t index) {
	return (bit_array->array[DIV_64(index)] >> MOD_64(index)) & (uint64_t)1;
}

void delete_bitmap(Bitmap* bit_array) {
	free(bit_array->array);
	free(bit_array);
}

bool is_uint32(char* beginning, uint64_t* converted, char** end) {
    int64_t test_converted = strtoll(beginning, end, R_BASE);
    if (test_converted < 0 || test_converted > UINT32_MAX) {
        return false;
    }
    else {
        *converted = (uint64_t)test_converted;

        return true;
    }
}

Bitmap* convert_r_to_bitmap(char* r, size_t labyrinth_length) {
	uint32_t coefficients[NUM_COEFF] = {0, 0, 0, 0, 0};
	int counter = 0;
	uint64_t converted;

    // Move pass the 'R' sign
    r++;
    bool correct_uint32_range;
    char* spare_string = NULL;
	while (counter < NUM_COEFF && *r != '\0' && *r != '\n' && *r != EOF) {
		while (isspace(*r) && *r != '\0' && *r != '\n' && *r != EOF) {
			r++;
		}

		if  (!isdigit(*r)) {
            return NULL;
		}

        correct_uint32_range = is_uint32(r, &converted,
                                         &spare_string);

        if (!correct_uint32_range) {
            return NULL;
        }

        coefficients[counter++] = (uint32_t)converted;
        r = spare_string;
	}

    if (coefficients[M_POS] == 0 || counter < NUM_COEFF) {

        return NULL;
    }

	if (counter == NUM_COEFF) {
		while (isspace(*r) && *r != '\0' && *r != '\n' && *r != EOF) {
			r++;
		}

        // Any type of non-ending sign is incorrect
		if (*r != '\0' && *r != '\n' && *r != EOF) {
            return NULL;
		}
	}

    // Since we perform modulo operation on w_i with both M or n_1*...*n_k,
    // the possible range of the w_i cannot be greater than the smaller
    // of M and n_1*...*n_k
	Bitmap* modulo;
	if (coefficients[M_POS] < labyrinth_length) {
		modulo = create_bitmap(coefficients[M_POS]);
	}
	else {
		modulo = create_bitmap(labyrinth_length);
	}


	uint32_t s_i = coefficients[S_POS];
    uint32_t w_i;

    // Modulo arithmetic performed for overflow prevention
    for (uint32_t i = 0; i < coefficients[R_POS]; i++) {
        s_i = (((coefficients[A_POS]%coefficients[M_POS])*
                (s_i%coefficients[M_POS])) % coefficients[M_POS] +
                coefficients[B_POS]%coefficients[M_POS]) % coefficients[M_POS];

        w_i = s_i%labyrinth_length;
        set_bit(modulo, (uint64_t)w_i);
    }

    return modulo;
}





