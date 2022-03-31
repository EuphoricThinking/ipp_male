#include "bit_lab_utils.h"
#include <string.h>


#define A_VAL 10
#define B_VAL 11
#define C_VAL 12
#define D_VAL 13
#define E_VAL 14
#define F_VAL 15

int return_hex_val(char sign) {
	if (sign == 'A' || sign == 'a') return A_VAL;
	else if (sign == 'B' || sign == 'b') return B_VAL;
	else if (sign == 'C' || sign == 'c') return C_VAL;
	else if (sign == 'D' || sign == 'd') return D_VAL;
	else if (sign == 'E' || sign == 'e') return E_VAL;
	else if (sign == 'F' || sign == 'f') return F_VAL;
	else return sign - '0';
}

Bitmap* create_bitmap(size_t length) {
	uint64_t* bit_array = malloc(sizeof(uint64_t)*DIV_64(length));

	Bitmap* result = malloc(sizeof(Bitmap));
	result->size = length;
	result->array = bit_array;

	return result;
}

Bitmap* convert_to_hex_bitmap(const char* hex, size_t length);



void set_bit(Bitmap* bit_array, unsigned long long index) {
	bit_array[DIV_64(index)] |= (1ULL << (index - 1));
}

bool isEmptyCell(Bitmap* bit_array, unsigned long long index) {
	if (bitarray[DIV_64(index)] & (1ULL << MOD_64(index))] == 0) return false;
	return true;
}



