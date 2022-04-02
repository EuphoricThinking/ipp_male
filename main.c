#include "input_utils.h"
#include "bit_lab_utils.h"
#include "labyrinth.h"

int main() {
    Labyrinth* loaded = read_and_process_input();
    run_BFS(loaded);

	return 0;
}
