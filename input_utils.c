#define _POSIX_C_SOURCE 200809L
#include "input_utils.h"
#include "err.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BASE 10
bool check_if_correct(char* read, size_t length) {
        for (int i = 0; i < length; i++) {
                if (!isdigit(read[i]) || !isspace(read[i])) {
                    return false;
                }
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
    char* next_string = NULL;
    size_t converted;

    while (next_string != NULL && (*next_string == '\n'
        || *next_string == '\0')) {
        converted = (size_t)strtoull(to_pass, next_string, BASE);
        if (converted ==
        0) {
            return NULL;
        }
        to_pass = next_string;
        number_array[index++] = converted;
    }

    Arr_len* res = create_Arr_len(number_array, index);
    return res;
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
