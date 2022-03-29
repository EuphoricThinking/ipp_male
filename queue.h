#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef struct List {
	unsigned long long val;
	struct List* next;
} List;

typedef struct Queue {
	List* first;
	List* last;

	int num_elements;
} Queue;

extern void push(Queue* q, unsigned long long val);

extern unsigned long long top(Queue* q);

extern unsigned long long pop(Queue* q);

extern void deleteQueue(Queue* q);

extern Queue* initQueue();

extern bool isEmpty(Queue* q);
#endif /* QUEUE_H */
