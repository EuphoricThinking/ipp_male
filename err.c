#include "err.h"

void print_error(const int error_label) {
	fprintf(stderr, "ERROR %d\n", error_label - 1);
}
