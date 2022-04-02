#define _POSIX_C_SOURCE 200809L
#include "input_utils.h"
#include "err.h"
#include "labyrinth.h"
#include "bit_lab_utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define BASE 10
bool has_only_whitespace(char* read) {
    size_t index = 0;
    while (read[index] != '\n' && read[index] != EOF && read[index] != '\0') {
        if (!isspace(read[index])) {
            return false;
        }

        index++;
    }

    return true;
}

bool check_if_correct(char* read) {
        size_t index = 0;
        while (read[index] != '\n' && read[index] != EOF && read[index] != '\0') {
            if (!isdigit(read[index]) && !isspace(read[index])) {
                    return false;
            }

            index++;
        }

        if (has_only_whitespace(read)) {
            return false;
        }

        return true;
}

uint64_t get_labyrinth_size(size_t* dimensions, size_t length) {
    uint64_t result = dimensions[0];
    for (size_t i = 1; i < length; i++) {
        result *= (uint64_t)dimensions[i];
        if (result > SIZE_MAX) {
            return -1;
        }
    }

    return result;
}

size_t* convert_to_size_t_array(char* read_input, size_t* length_after_processing) {
    size_t* number_array = malloc(sizeof(size_t));
    size_t allocated_size = sizeof(size_t);
    size_t current = 0;

    if (!number_array) {
        return NULL;
    }

    size_t index = 0;
    char* to_pass = read_input;
    char* next_string;
    size_t converted;
    size_t* err;
    while (*to_pass != '\0' && *to_pass != '\n' && *to_pass != EOF) {
        converted = strtoull(to_pass, &next_string, BASE);
        if (converted > SIZE_MAX || converted < 1 || errno == ERANGE) {
            free(number_array);
            return NULL;
        }

        to_pass = next_string;
        number_array[index++] = (size_t) converted;
        current += sizeof(size_t);

        if (current == allocated_size) {
            allocated_size = 2*current;
            err = realloc(number_array, allocated_size);
            if (!err) {
                print_error(ERR_0);
                exit(1);
            }
            else {
                number_array = err;
            }
        }

        while (isspace(*to_pass) && *to_pass != '\0' && *to_pass != EOF) {
            to_pass++;
        }
    }

    if (errno == ERANGE) {
        return NULL;
    }

    *length_after_processing = index;

    return number_array;
}

char* determine_mode(char* read) {
    while (isspace(*read) && *read != '\0' && *read != '\n' && *read != EOF) {
        read++;
    }

    if ((*read != '0' && *read != 'R') || (*read == '0' && *(read + 1) != 'x')) {
        return NULL;
    }

    return read;
}

void release_final(char* workline, size_t* dimensions_sizes,
           size_t* start_coordinates, size_t* end_coordinates, int err_code) {
    free(workline);
    free(dimensions_sizes);
    free(start_coordinates);
    free(end_coordinates);
    print_error(err_code);
    exit(1);
}

bool is_bigger_than_dimension(size_t* dimensions, size_t num_dimensions,
                                    size_t* to_check) {
    for (size_t i = 0; i < num_dimensions; i++) {
        if (dimensions[i] < to_check[i]) {
            return true;
        }
    }

    return false;
}

Labyrinth* read_and_process_input() {
	char* workline = NULL;
	size_t getline_buffer;

    // Wcytaj wymiary
	if (getline(&workline, &getline_buffer, stdin) < 1
        || !check_if_correct(workline)) {

        release_final(workline, NULL, NULL, NULL, ERR_1);
    }

    size_t num_dimensions;
    size_t* dimensions_sizes = convert_to_size_t_array(workline,
                                                       &num_dimensions);

    if (dimensions_sizes == NULL) {
        release_final(workline, NULL, NULL, NULL, ERR_1);
    }

    uint64_t labyrinth_size = get_labyrinth_size(dimensions_sizes, num_dimensions);
    if (labyrinth_size < 1) {
        release_final(workline, dimensions_sizes, NULL,
                      NULL, ERR_0);
    }
    // Wczytaj start
    if (getline(&workline, &getline_buffer, stdin) < 1
        || !check_if_correct(workline)) {
        release_final(workline, dimensions_sizes, NULL, NULL, ERR_2);
    }

    size_t read_numbers;
    size_t* start_coordinates = convert_to_size_t_array(workline,
                                                        &read_numbers);
    if (start_coordinates == NULL || read_numbers != num_dimensions
        || is_bigger_than_dimension(dimensions_sizes, num_dimensions,
                                        start_coordinates)) {
        release_final(workline, dimensions_sizes, NULL, NULL, ERR_2);
    }

    // Wczytaj koniec
    if (getline(&workline, &getline_buffer, stdin) < 1
        || !check_if_correct(workline)) {
        release_final(workline, dimensions_sizes, start_coordinates, NULL,
                      ERR_3);
    }

    size_t* end_coordinates = convert_to_size_t_array(workline,
                                                      &read_numbers);
    if (end_coordinates == NULL || read_numbers != num_dimensions
        || is_bigger_than_dimension(dimensions_sizes, num_dimensions,
                                        end_coordinates)) {
        release_final(workline, dimensions_sizes, start_coordinates,
                      end_coordinates, ERR_3);
    }

    // Wczytaj liczbę
    if (getline(&workline, &getline_buffer, stdin) < 1) {
        release_final(workline, dimensions_sizes, start_coordinates,
                      end_coordinates, ERR_4);
    }

    // Skrócenie do pierwszych znaków określających liczbę
    char* shortened = determine_mode(workline);

    if (!shortened) {
        release_final(workline, dimensions_sizes, start_coordinates,
                      end_coordinates, ERR_4);
    }

    Labyrinth* result;
    if (*shortened == 'R') {
        Bitmap* modulo = convert_r_to_bitmap(shortened, labyrinth_size); //read_width
        if (!modulo) { // Allocation errors are handled in bit.h
            release_final(workline, dimensions_sizes, start_coordinates,
                          end_coordinates, ERR_4);
        }

        Bitmap* to_be_filled = create_bitmap(labyrinth_size);
        result = load_labyrinth(labyrinth_size, num_dimensions, dimensions_sizes,
                                start_coordinates, end_coordinates, true,
                                to_be_filled, modulo);
    }
    else {
        Bitmap* filled_from_hex = convert_hex_to_bitmap(shortened,
                                                        strlen(shortened), labyrinth_size);
        if (!filled_from_hex) {
            release_final(workline, dimensions_sizes, start_coordinates, end_coordinates,
                          ERR_4);
        }
        result = load_labyrinth(labyrinth_size, num_dimensions, dimensions_sizes,
                                start_coordinates, end_coordinates, false,
                                filled_from_hex, NULL);
    }

    // Sprawdzenie ostatniej linii
    char* test_last_line = NULL;
    size_t test_read;
    if (getline(&test_last_line, &test_read, stdin) > 0) {
        free(test_last_line);
        free(workline);
        delete_labyrinth(result);
        print_error(ERR_5);

        exit(1);
    }

    free(test_last_line);
    free(workline);

	return result;
}
