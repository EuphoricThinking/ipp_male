#ifndef LABYRINTH_H
#define LABYRINTH_H
#include "bit_lab_utils.h"
#include <stdint.h>

extern Labyrinth* load_labyrinth(uint64_t size, size_t num_dimensions,
                                 size_t* dimensions_sizes, size_t* start_coordinates,
                                 size_t* end_coordinates, bool R_mode, Bitmap* bit_array,
                                 Bitmap* modulo);

extern void delete_labyrinth(Labyrinth* to_delete);

extern void run_BFS(Labyrinth* loaded);

#endif
