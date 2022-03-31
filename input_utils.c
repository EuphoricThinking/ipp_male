#define _POSIX_C_SOURCE 200809L
#include "input_utils.h"
#include "err.h"
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

typedef struct Arr_len {
        size_t* arr;
        size_t len;
} Arr_len;

Arr_len* create_Arr_len(size_t* arr, size_t len) {
    Arr_len* res = malloc(sizeof(Arr_len));

    res->arr = arr;
    res->len = len;
    return res;
}

void delete_Arr_len(Arr_len* pair) {
        free(pair->arr);
        free(pair);
}

Arr_len* convert_to_size_t(char* read_input, size_t max_length) {
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

    Arr_len* res = create_Arr_len(number_array, index);
    return res;
}

Arr_len* determine_mode(char* read, size_t read_length) {
    while
}
Labirynth read_input() {
	char* dimension_sizes = NULL;
	size_t read_width;

	if (getline(&dimension_sizes, &read_width, stdin) < 1
        || !check_if_correct(dimension_sizes, read_width)) {
            free(dimension_sizes);
            print_error(ERR_1);
            exit(0);
    }

    char* start_array = NULL;
//    size_t beginning_size;
    if (getline(&start_array, &read_width, stdin) < 1
        || !check_if_correct(start_array, read_width)) {
        free(dimension_sizes);
        free(start_array);
        print_error(ERR_1);
        exit(1);
    }

    char* end_array = NULL;
    if (getline(&end_array, &read_width, stdin) < 1
        || !check_if_correct(end_array, read_width)) {
        free(dimension_sizes);
        free(start_array);
        free(end_array);
        print_error(ERR_1);
        exit(1);
    }

	Labirynth l;
	return l;
}
