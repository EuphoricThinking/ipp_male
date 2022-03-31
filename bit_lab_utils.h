#ifndef LABIRYNTH_STRUCT_H
#define LABIRYNTH_STRUCT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define DIV_64(x) (x >> 6)
#define MOD_64(x) (x & (((uint64_t)1 << 6) - 1))

typedef struct Cube {
	size_t* coordinates;
	size_t num_dimension;
} Cube;

typedef struct Bitmap {
        unsigned long long length;
        uint64_t* array;
} Bitmap;

typedef struct Labirynth {
	unsigned long long labirynth_size;
	size_t num_dimensions;
	size_t* dimension_sizes;
	size_t* start_coordinates;
	size_t* end_coordinates;

	int mode;
	struct Bitmap bit_array;
} Labirynth;

extern Bitmap* convert_hex_to_bitmap(const char* hex, size_t lenght);

extern void set_bit(Bitmap* bit_array, unsigned long long index);

extern Bitmap* create_bitmap(size_t length);

extern bool isEmptyCell(Bitmap* bit_array, unsigned long long index);
#endif


