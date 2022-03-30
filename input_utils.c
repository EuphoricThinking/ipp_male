#include "input_utils.h"
#include "err.h"

Labirynth* read_input() {
	char* line = dimension_sizes;
	size_t dimensions;

	if (getline(&dimension_sizes, &dimensions, stdin) < 1) {
		print_error(ERR_1);
		exit(1);
	}
}
