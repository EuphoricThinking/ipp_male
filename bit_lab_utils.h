#ifndef LABIRYNTH_STRUCT_H
#define LABIRYNTH_STRUCT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define DIV_64(x) ((x) >> 6)
#define MOD_64(x) ((x) & (((uint64_t)1 << 6) - 1))

typedef struct Cube {
	size_t* coordinates;
	size_t num_dimension;
} Cube;

typedef struct Bitmap {
        uint64_t length;
        uint64_t* array;
} Bitmap;

typedef struct Labyrinth {
	uint64_t size;
	size_t num_dimensions;
	size_t* dimension_sizes;
	size_t* start_coordinates;
	size_t* end_coordinates;

	bool R_mode;
	struct Bitmap* bit_array;
	struct Bitmap* modulo_array;
} Labyrinth;

extern Bitmap* convert_r_to_bitmap(char* r, size_t r_length, size_t labyrinth_length);

extern Bitmap* convert_hex_to_bitmap(char* hex, size_t hex_length, uint64_t labyrinth_size);

extern void set_bit(Bitmap* bit_array, uint64_t index);

extern Bitmap* create_bitmap(size_t length);

extern bool is_empty_cell(Bitmap* bit_array, uint64_t index);

extern void delete_bitmap(Bitmap* bit_array);
#endif


