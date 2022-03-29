#ifndef QUEUE_H
#define QUEUE_H

typedef struct List {
	unsigned long long val;
	List* next;
} List;

typedef struct Queue {
	List* first;
	List* last;
} queue;

void push(unsigned long long val);

unsigned long long top();

unsigned long long pop();

#endif /* QUEUE_H */
