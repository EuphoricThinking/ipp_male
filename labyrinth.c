#include "labyrinth.h"
#include <stdlib.h>
#include "err.h"
#include "queue.h"

#define NO_WAY "NO WAY\n"

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

void delete_labyrinth(Labyrinth* to_delete) {
    free(to_delete->dimension_sizes);
    free(to_delete->start_coordinates);
    free(to_delete->end_coordinates);
    delete_bitmap(to_delete->bit_array);
    if (to_delete->R_mode) delete_bitmap(to_delete->modulo_array);

    free(to_delete);
}

uint64_t find_index(size_t* coordinates, size_t* dimension_sizes,
                    uint64_t length) {
    uint64_t index = coordinates[0] - 1;
    uint64_t multiplier = 1;

    for (uint64_t i = 1; i < length; i++) {
        multiplier *= (uint64_t)dimension_sizes[i - 1];
        index += ((uint64_t)coordinates[i] - (uint64_t)1)*multiplier;
    }

    return index;
}

void find_coordinates(size_t* coordinates, size_t* dimension_sizes,
                      uint64_t length, uint64_t index) {
    uint64_t rest_to_divide = index;
    uint64_t remainder;

    for (uint64_t i = 0; i < length - 1; i++) {
        remainder = rest_to_divide % dimension_sizes[i];
        rest_to_divide /= dimension_sizes[i];
        coordinates[i] = (size_t)(remainder + 1);
    }

    coordinates[length - 1] = rest_to_divide + 1;
}

bool is_not_available(Labyrinth* data, uint64_t index) {
    if (data->R_mode) {
        return is_filled_cell(data->modulo_array, MOD_2_32(index))
            || is_filled_cell(data->bit_array, index);
    }
    else {
        return is_filled_cell(data->bit_array, index);
    }
}

void make_unavailable(Labyrinth* data, uint64_t index) {
    set_bit(data->bit_array, index);
}

void push_neighbours(size_t* coordinates, Labyrinth* data, Queue* neighbours,
                     uint64_t current_depth) {
    size_t original;
    uint64_t neighbour_index;

    for (uint64_t index = 0; index < data->num_dimensions; index++) {

        original = coordinates[index];

        for (int diff = -1; diff <= 1; diff += 2) {
            coordinates[index] = original + diff;

            if (coordinates[index]  > 0 && coordinates[index] <= data->dimension_sizes[index]) {
                neighbour_index = find_index(coordinates, data->dimension_sizes,
                                             data->num_dimensions);

                if (!is_not_available(data, neighbour_index)) {
                    push(neighbours, neighbour_index, current_depth + 1);
                    make_unavailable(data,neighbour_index);                    // PRZEMYŚL, CZY NIE ZA DUŻO
                }
            }
        }

        coordinates[index] = original;
    }
}

size_t* copy_coordinates(size_t* coordinates, size_t length) {
    size_t* copied = malloc(length*sizeof(size_t));

    for (size_t i = 0; i < length; i++) {
        copied[i] = coordinates[i];
    }

    return copied;
}

void final_release(Queue* neighbours, Labyrinth* loaded,
                   size_t* temp_coordinates, List* current_cell) {
    delete_queue(neighbours);
    delete_labyrinth(loaded);
    if (current_cell) {
        delete_node(current_cell);
    }
    free(temp_coordinates);
}

void exit_error(Labyrinth* loaded, int error_code) {
    print_error(error_code);
    delete_labyrinth(loaded);

    exit(1);
}
void run_BFS(Labyrinth* data) {
    uint64_t start_index = find_index(data->start_coordinates,
                                          data->dimension_sizes,
                                          data->num_dimensions);
    if (is_not_available(data, start_index)) {
        exit_error(data, ERR_2);
    }

    uint64_t end_index = find_index(data->end_coordinates, data->dimension_sizes,
                                    data->num_dimensions);

    if (is_not_available(data, end_index)) {
        exit_error(data, ERR_3);
    }

    if (start_index == end_index) {
        delete_labyrinth(data);
        printf("%d\n", 0);

        return;
    }

    Queue* neighbours = init_queue();
    size_t* coordinates_to_overwrite = copy_coordinates(data->start_coordinates,
                                                        data->num_dimensions);
    push_neighbours(coordinates_to_overwrite, data, neighbours, 0);
    make_unavailable(data, start_index);
    List* current_neighbour;
    uint64_t road_length;

    while (!is_empty(neighbours)) {
        current_neighbour = pop(neighbours);

        if (current_neighbour->val == end_index) {
            road_length = current_neighbour->depth;
            final_release(neighbours, data, coordinates_to_overwrite,
                          current_neighbour);

            printf("%lu\n", road_length); //RES

            return;
        }

        find_coordinates(coordinates_to_overwrite, data->dimension_sizes,
                         data->num_dimensions, current_neighbour->val);
        push_neighbours(coordinates_to_overwrite, data, neighbours,
                        current_neighbour->depth);
        delete_node(current_neighbour);
    }

    final_release(neighbours, data, coordinates_to_overwrite, NULL);

    printf(NO_WAY);
}