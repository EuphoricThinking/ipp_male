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

#define BIAS 		(uint64_t)63U
#define NUM_4_BIT_SUBCELLS 16
#define HEX_CELL	(uint64_t)4

#define A_POS 0
#define B_POS 1
#define M_POS 2
#define R_POS 3
#define S_POS 4
#define NUM_COEFF 5
#define R_BASE 10

uint64_t return_hex_val(char sign) {
	if (sign == 'A' || sign == 'a') return A_VAL;
	else if (sign == 'B' || sign == 'b') return B_VAL;
	else if (sign == 'C' || sign == 'c') return C_VAL;
	else if (sign == 'D' || sign == 'd') return D_VAL;
	else if (sign == 'E' || sign == 'e') return E_VAL;
	else if (sign == 'F' || sign == 'f') return F_VAL;
	else if (isdigit(sign)) return (uint64_t)(sign - '0');
	else return HEX_ERROR;
	//isdigit - redurnt
}

Bitmap* create_bitmap(size_t length) {
//	uint64_t* bit_array = malloc(sizeof(uint64_t)*DIV_64(length));
	size_t cell_number = DIV_64(length + BIAS);
	uint64_t* bit_array = malloc(sizeof(uint64_t)*(cell_number));  //roundup

    if (!bit_array) {
        print_error(ERR_0);
        exit(1);
    }

	for (uint64_t i = 0; i < length; i++) {
		bit_array[i] = (uint64_t)0;
	}

	Bitmap* result = malloc(sizeof(Bitmap));
	result->length = cell_number;
	result->array = bit_array;

	return result;
}

/*
	Hex index nie będzie ujemne, ponieważ zatrzymamy się na 'x';
	od końca przechodzi hex_index, od początku przechodzi array

	Sprawdź, czy liczba nie jest za długa
*/
Bitmap* convert_to_hex_bitmap(const char* hex, size_t hex_length, size_t labirynth_size) {
	uint64_t hex_index = hex_length - 1;
	if (hex[hex_index] == 'x') {
		print_error(ERR_4);
		//exit(1);
        return NULL;
	}

	uint64_t hex_converted;
	uint64_t shift;
	int bit_quartet;
	uint64_t cell = 0;

	Bitmap* converted = create_bitmap(labirynth_size);

	while (cell < converted->length && hex[hex_index] != 'x') {
		shift = 0;
		bit_quartet = 0;
		while (bit_quartet < NUM_4_BIT_SUBCELLS) {
			while (isspace(hex[hex_index])) hex_index--;
			if (hex[hex_index] == 'x') break;

			hex_converted = return_hex_val(hex[hex_index--]);
			if (hex_converted == HEX_ERROR) {
				print_error(ERR_4);
				delete_bitmap(converted);
				//exit(1);
                return NULL;
			}

			converted->array[cell] |= (hex_converted << shift);
			shift += 4;
			bit_quartet++;
		}

		if (hex[hex_index] != 'x') cell++;
		else break;
	}

	if (cell == converted->length) {
		bool not_finished = true;
		while (not_finished) {
			while (isspace(hex[hex_index])) hex_index--;

			if (hex[hex_index] == 'x') {
				not_finished = false;
			}
			else if (hex[hex_index] != '0') {
				print_error(ERR_4);
				delete_bitmap(converted);
				//exit(1);
                return NULL;
			}
		}
	}

	return converted;
}



void set_bit(Bitmap* bit_array, uint64_t index) {
	bit_array->array[DIV_64(index)] |= ((uint64_t)1 << (index - 1));
}

bool is_filled_cell(Bitmap* bit_array, uint64_t index) {
//	if (((bit_array->array[DIV_64(index)] >> MOD_64(index)) & (uint64_t)1) == 0) return false;
//	return true;
	return (bit_array->array[DIV_64(index)] >> MOD_64(index)) & (uint64_t)1;
}

void delete_bitmap(Bitmap* bit_array) {
	free(bit_array->array);
	free(bit_array);
}

bool check_correct(char* number) {
//	if (!isdigit(c)) return false;
//	if (r_number << 32 & (((uint64_t)1 << 63) - 1) != 0) return false;
	while (!isspace(*number)) {}
	return true;
}

Bitmap* convert_r_to_bitmap(char* r, size_t r_length, size_t labirynth_length) {
	uint32_t coefficients[NUM_COEFF];
	int counter = 0;
	uint32_t converted;

	while (*r != 'R' && r_length > 0) {
		r++;
		r_length--;
	}

	while (counter < NUM_COEFF && r_length > 0) {
		while (isspace(*r) && r_length > 0) {
			r++;
			r_length--;
		}

		if (r_length <= 0 || !isdigit(*r)) { //za mało
			print_error(ERR_4);
			//exit(1);
            return NULL;
		}

		converted = (uint32_t)atol(r);
		coefficients[counter++] = converted;

		while (isdigit(*r) && r_length > 0) r++;
	}

    if (coefficients[M_POS] == 0) {
        print_error(ERR_4);
        return NULL;
    }

	if (counter == NUM_COEFF && r_length > 0) {
		while (isspace(*r) && r_length > 0) {
			r++;
			r_length--;
		}

		if (r_length > 0) { //jakikolwiek niepusty znak | za dużo
			print_error(ERR_4);
			//exit(1);
            return NULL;
		}
	}

	Bitmap* modulo;
	if (r_length < labirynth_length) {
		modulo = create_bitmap(r_length);
	}
	else {
		modulo = create_bitmap(labirynth_length);
	}

	uint32_t s_i = coefficients[S_POS];
    uint32_t w_i;
    for (uint32_t i = 0; i < coefficients[R_POS]; i++) {
        s_i = (coefficients[A_POS]*s_i + coefficients[B_POS])
                %coefficients[M_POS];
        w_i = s_i%labirynth_length;
        set_bit(modulo, (uint64_t)w_i);
    }

    return modulo;
}





