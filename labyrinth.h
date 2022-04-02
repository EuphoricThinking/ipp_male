#ifndef LABYRINTH_H
#define LABYRINTH_H
#include "bit_lab_utils.h"
#include <stdint.h>

/*
 * A structure storing the input and the preprocessed data,
 * on which BFS can be performed
 */

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

extern Labyrinth* load_labyrinth(uint64_t size, size_t num_dimensions,
                                 size_t* dimensions_sizes, size_t* start_coordinates,
                                 size_t* end_coordinates, bool R_mode, Bitmap* bit_array,
                                 Bitmap* modulo);

extern void delete_labyrinth(Labyrinth* to_delete);

extern void run_BFS(Labyrinth* loaded);

#endif
