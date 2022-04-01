#include "labirynth.h"
#include <stdlib.h>
#include "err.h"

Labyrinth* load_labyrinth(uint64_t size, size_t num_dimensions,
	size_t* dimensions_sizes, size_t* start_coordinates,
	size_t* end_coordinates, bool R_mode, Bitmap* bit_array,
	Bitmap* modulo) {
	Labyrinth* loaded = malloc(sizeof(Labyrinth));
    if (!loaded) {
        print_error(ERR_0);
        exit(1);
    }

	loaded->size = size;
	loaded->num_dimensions = num_dimensions;
	loaded->dimension_sizes = dimensions_sizes;
    loaded->start_coordinates = start_coordinates;
    loaded->end_coordinates = end_coordinates;
    loaded->R_mode = R_mode;
    loaded->bit_array = bit_array;
    loaded->modulo_array = modulo;

    return loaded;
}
