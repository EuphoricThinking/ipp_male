#ifndef QUEUE_H
#define QUEUE_H

typedef struct List {
	unsigned long long val;
	List* next;
} List;

typedef struct Queue {
	List* first;
	List* last;

	int num_elements;
} Queue;

extern void push(unsigned long long val, Queue* q);

extern unsigned long long top(Queue* q);

extern unsigned long long pop(Queue* q);

extern void deleteQueue(Queue* q);

extern Queue* initQueue();

extern isEmpty(Queue* q);
#endif /* QUEUE_H */
