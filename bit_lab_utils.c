#include "bit_lab_utils.h"

Bitmap* convert_to_hex_bitmap(const char* hex, size_t length);



void set_bit(Bitmap* bit_array, unsigned long long index) {
	bit_array[DIV_64(index)] |= (1ULL << (index - 1));
}

bool isEmptyCell(Bitmap* bit_array, unsigned long long index) {
	if (bitarray[DIV_64(index)] & (1ULL << MOD_64(index))] == 0) return false;
	return true;
}



