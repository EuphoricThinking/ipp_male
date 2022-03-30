#define _POSIX_C_SOURCE 200809L
#include "input_utils.h"
#include "err.h"
#include <stdio.h>

Labirynth read_input() {
	char* dimension_sizes = NULL;
	size_t dimensions;

	if (getline(&dimension_sizes, &dimensions, stdin) < 1) {
		print_error(ERR_1);
		exit(1);
	}

	Labirynth l;
	return l;
}
