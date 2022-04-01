#ifndef LABIRYNTH_H
#define LABIRYNTH_H
#include "bit_lab_utils.h"

extern Labirynth* load_labirynth(uint64_t size, size_t num_dimensions,
	size_t* dimensions_sizes, size_t* start_coordinates,
	size_t* end_coordinates, bool R_mode, Bitmap* bit_array,
	Bitmap* modulo);
#endif
