#define _POSIX_C_SOURCE 200809L
#include "input_utils.h"
#include "err.h"
#include "labirynth.h"
#include "bit_lab_utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BASE 10
bool has_only_whitespace(char* read, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (!isspace(read[i])) {
            return false;
        }
    }

    return true;
}

bool check_if_correct(char* read, size_t length) {
        for (size_t i = 0; i < length; i++) {
                if (!isdigit(read[i]) && !isspace(read[i])) {
                    return false;
                }
        }

        if (has_only_whitespace(read, length)) {
            return false;
        }

        return true;
}

uint64_t get_labirynth_size(size_t* dimensions, size_t length) {
    uint64_t result = dimensions[0];
    for (size_t i = 1; i < length; i++) {
        result *= dimensions[i];
    }

    return result;
}

size_t* convert_to_size_t(char* read_input, size_t max_length, size_t* length_after_processing) {
    size_t* number_array = malloc(sizeof(size_t)*max_length);
    if (!number_array) {return NULL;}
    size_t index = 0;
    char* to_pass = read_input;
    char* next_string;
    size_t converted;

    converted = (size_t) strtoull(to_pass, &next_string, BASE);
    while (converted > 0) {
        to_pass = next_string;
        number_array[index++] = converted;
        converted = (size_t) strtoull(to_pass, &next_string, BASE);
    }

    *length_after_processing = index;
    return number_array;
}

char* determine_mode(char* read, size_t* read_length) {
    while (*read != 'R' && (*read != '0' && *read != 'x') && *read_length > 0) {
        read++;
        (*read_length)--;
    }

    if (*read_length == 0) return NULL;
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
Labirynth* read_input() {
	char* workline = NULL;
	size_t read_width;
    ssize_t err;

	if ((err = getline(&workline, &read_width, stdin)) < 1
        || !check_if_correct(workline, read_width)) {
            free(workline);
            if (err < 0) {
                print_error(ERR_0);
            }
            else {
                print_error(ERR_1);
            }
            exit(0);
    }

    size_t num_dimensions;
    size_t* dimensions_sizes = convert_to_size_t(workline,
                     read_width, &num_dimensions);
    if (dimensions_sizes == NULL) {
        free(workline);
        print_error(ERR_0);
        exit(1);
    }

    if ((err = getline(&workline, &read_width, stdin)) < 1
        || !check_if_correct(workline, read_width)) {
        free(workline);
        free(dimensions_sizes);
        if (err < 1) {
            print_error(ERR_0);
        }
        else {
            print_error(ERR_1);
        }
        exit(1);
    }
    size_t read_numbers;
    size_t* start_coordinates = convert_to_size_t(workline,
                          read_width, &read_numbers);
    if (start_coordinates == NULL) {
        free(workline);
        free(dimensions_sizes);
        print_error(ERR_0);
        exit(1);
    }

    if ((err = getline(&workline, &read_width, stdin)) < 1
        || !check_if_correct(workline, read_width)
        || read_numbers != num_dimensions) {
        free(workline);
        free(dimensions_sizes);
        free(start_coordinates);
        print_error(ERR_2);
        exit(1);
    }

    size_t* end_coordinates = convert_to_size_t(workline,
                                    read_width, &read_numbers);
    if (end_coordinates == NULL || read_numbers != num_dimensions) {
        free(workline);
        free(dimensions_sizes);
        free(start_coordinates);
        if (read_numbers != num_dimensions) {
            print_error(ERR_3);
        }
        else {
            print_error(ERR_0);
        }
        exit(1);
    }

    if (getline(&workline, &read_width, stdin) < 1) {
        free(workline);
        free(dimensions_sizes);
        free(start_coordinates);
        free(end_coordinates);
        print_error(ERR_0);
        exit(1);
    }

    char* shortened = determine_mode(workline, &read_width);

    if (!shortened) {
        free(workline);
        free(dimensions_sizes);
        free(start_coordinates);
        free(end_coordinates);
        print_error(ERR_4);
        exit(1);
    }

    uint64_t labirynth_size = get_labirynth_size(dimensions_sizes, num_dimensions);

    Labirynth* result;
    if (*shortened == 'R') {
        Bitmap* modulo = convert_r_to_bitmap(shortened, read_width, labirynth_size);
        if (!modulo) {
            release_final(workline, dimensions_sizes, start_coordinates,
                          end_coordinates, ERR_4);
        }
        Bitmap* to_be_filled = create_bitmap(labirynth_size);
        result = load_labirynth(labirynth_size, num_dimensions, dimensions_sizes,
                                start_coordinates, end_coordinates, true,
                                to_be_filled, modulo);
    }
    else {
        Bitmap* filled_from_hex = convert_hex_to_bitmap(shortened, read_width, labirynth_size);
        if (!filled_from_hex) {
            release_final(workline, dimensions_sizes, start_coordinates, end_coordinates,
                          ERR_4);
        }
        result = load_labirynth(labirynth_size, num_dimensions, dimensions_sizes,
                                start_coordinates, end_coordinates, false,
                                filled_from_hex, NULL);
    }

	return result;
}
