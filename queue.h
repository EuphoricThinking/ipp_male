#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include <stdint.h>

typedef struct List {
	uint64_t val;
    uint64_t depth;
	struct List* next;
} List;

typedef struct Queue {
	List* first;
	List* last;

	int num_elements;
} Queue;

extern void push(Queue* q, uint64_t val, uint64_t depth);

extern List* top(Queue* q);

extern List* pop(Queue* q);

extern void deleteQueue(Queue* q);

extern Queue* initQueue();

extern void deleteNode(List* node);

extern bool isEmpty(Queue* q);
#endif /* QUEUE_H */
