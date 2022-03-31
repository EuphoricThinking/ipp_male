#include "bit_lab_utils.h"
#include <string.h>


#define A_VAL 10ULL
#define B_VAL 11ULL
#define C_VAL 12ULL
#define D_VAL 13ULL
#define E_VAL 14ULL
#define F_VAL 15ULL

#define BIAS 63ULL

unsigned long long return_hex_val(char sign) {
	if (sign == 'A' || sign == 'a') return A_VAL;
	else if (sign == 'B' || sign == 'b') return B_VAL;
	else if (sign == 'C' || sign == 'c') return C_VAL;
	else if (sign == 'D' || sign == 'd') return D_VAL;
	else if (sign == 'E' || sign == 'e') return E_VAL;
	else if (sign == 'F' || sign == 'f') return F_VAL;
	else return (unsigned long long)(sign - '0');
}

Bitmap* create_bitmap(size_t length) {
//	uint64_t* bit_array = malloc(sizeof(uint64_t)*DIV_64(length));
	size_t cell_number = DIV_64(length + BIAS);
	uint64_t bit_array = malloc(sizeof(uint64_t)*(cell_number);  //roundup
	for (uint64_t i = 0; i < length; i++) {
		bit_array[i] = (uint64_t)0;
	}

	Bitmap* result = malloc(sizeof(Bitmap));
	result->length = cell_number;
	result->array = bit_array;

	return result;
}

Bitmap* convert_to_hex_bitmap(const char* hex, size_t length);



void set_bit(Bitmap* bit_array, unsigned long long index) {
	bit_array[DIV_64(index)] |= (1ULL << (index - 1));
}

bool isEmptyCell(Bitmap* bit_array, unsigned long long index) {
//	if (bitarray[DIV_64(index)] & (1ULL << MOD_64(index))] == 0) return false;
	if (((bitarray[DIV_64(index)] >> MOD_64(index)) & (uint64_t)1) == 0) return false;
	return true;
}



