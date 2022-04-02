#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include <stdint.h>

typedef struct List {
	unsigned long long val;
	struct List* next;
} List;

typedef struct Queue {
	List* first;
	List* last;

	int num_elements;
} Queue;

extern void push(Queue* q, uint64_t val);

extern uint64_t top(Queue* q);

extern uint64_t pop(Queue* q);

extern void deleteQueue(Queue* q);

extern Queue* initQueue();

extern bool isEmpty(Queue* q);
#endif /* QUEUE_H */
