#include "err.h"

// Since 0 code is associated with the lack of errors, the constants
// are defined from 1, but in order to print them to stderr they are decremented.
void print_error(const int error_label) {
	fprintf(stderr, "ERROR %d\n", error_label - 1);
}
