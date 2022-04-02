#include <stdio.h>
#include "queue.h"
#include "input_utils.h"
#include "bit_lab_utils.h"
#include "labyrinth.h"

int main() {
//	Queue* q = initQueue();
//	push(q, 2);
//	push(q, 6);
//	push(q, 12);
//	//printf("%lld\n", top(q));
//
//	while (!isEmpty(q)) {
//		unsigned long long res_top = top(q);
//		unsigned long long res_pop = pop(q);
//		printf("%lld, %lld\n", res_top, res_pop);
//	}
//
//	deleteQueue(q);

    Labyrinth* loaded = read_and_process_input();
    printf("size: %ld\n", loaded->size);
    run_BFS(loaded);

//    Queue* q = init_queue();
//    push(q, 2, 4);
//    List* node = pop(q);
//    delete_node(node);
//    push(q, 5, 6);
//    node = pop(q);
//    delete_node(node);
//    delete_queue(q);

//    delete_labyrinth(loaded);

	return 0;
}
