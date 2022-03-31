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
#define NUM_4_BIT_SUBCELLS (uint64_t)16
#define HEX_CELL	(uint64_t)4
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
		exit(1);
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
			while (isspace(hex[hex_index]) == 0) hex_index--;
			if (hex[hex_index] == 'x') break;

			hex_converted = return_hex_val(hex[hex_index--]);
			if (hex_converted == HEX_ERROR) {
				print_error(ERR_4);
				delete_bitmap(converted);
				exit(1);
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
			print_error(ERR_0);
			delete_bitmap(converted);
			exit(1);
		}
	}

	return converted;
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



