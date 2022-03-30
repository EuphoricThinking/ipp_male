#ifndef LABIRYNTH_STRUCT_H
#define LABIRYNTH_STRUCT_H
#include <stddef.h>

typedef struct Cube {
	size_t* coordinates;
	size_t num_dimension;
} Cube;

typedef struct Labirynth {
	unsigned long long labirynth_size;
	size_t num_dimensions;
	size_t* dimension_sizes;
	size_t* start_coordinates;
	size_t* end_coordinates;
} Labirynth;

typedef struct Index_availability {
	unsigned int is_available: 1;
} Index_availability;

typedef struct Availability_array {
	struct Index_availability* available_indexes;
} Availability_array;

#endif


