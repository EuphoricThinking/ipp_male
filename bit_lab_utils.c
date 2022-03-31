#include "bit_lab_utils.h"
#include <string.h>
#include <stdlib.h>

#define A_VAL (uint64_t)10
#define B_VAL (uint64_t)11
#define C_VAL (uint64_t)12
#define D_VAL (uint64_t)13
#define E_VAL (uint64_t)14
#define F_VAL (uint64_t)15

#define BIAS 		(uint64_t)63U
#define NUM_4_BIT_CELLS (uint64_t)16
#define HEX_CELL	(uint64_t)4
uint64_t return_hex_val(char sign) {
	if (sign == 'A' || sign == 'a') return A_VAL;
	else if (sign == 'B' || sign == 'b') return B_VAL;
	else if (sign == 'C' || sign == 'c') return C_VAL;
	else if (sign == 'D' || sign == 'd') return D_VAL;
	else if (sign == 'E' || sign == 'e') return E_VAL;
	else if (sign == 'F' || sign == 'f') return F_VAL;
	else return (uint64_t)(sign - '0');
}

Bitmap* create_bitmap(size_t length) {
//	uint64_t* bit_array = malloc(sizeof(uint64_t)*DIV_64(length));
	size_t cell_number = DIV_64(length + BIAS);
	uint64_t* bit_array = malloc(sizeof(uint64_t)*(cell_number));  //roundup

	for (uint64_t i = 0; i < length; i++) {
		bit_array[i] = (uint64_t)0;
	}

	Bitmap* result = malloc(sizeof(Bitmap));
	result->length = cell_number;
	result->array = bit_array;

	return result;
}

Bitmap* convert_to_hex_bitmap(const char* hex, size_t length) {
	Bitmap* converted = create_bitmap(length);

	uint64_t hex_index = 0;
	uint64_t hex_converted;
	for (uint64_t cell = 0; cell < length; cell++) {
		for (uint64_t bit_quartet
	}
}



void set_bit(Bitmap* bit_array, uint64_t index) {
	bit_array->array[DIV_64(index)] |= ((uint64_t)1 << (index - 1));
}

bool is_empty_cell(Bitmap* bit_array, unsigned long long index) {
	if (((bit_array->array[DIV_64(index)] >> MOD_64(index)) & (uint64_t)1) == 0) return false;
	return true;
}

void delete_bitmap(Bitmap* bit_array) {
	free(bit_array->array);
	free(bit_array);
}



