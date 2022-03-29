#include "queue.h"
#include <stdlib.h>
#include <stddef.h>

List* initNode(unsigned long long val) {
	List* l = malloc(sizeof(List));

	l->next = NULL;
	l->val = val;

	return l;
}

Queue* initQueue() {
	Queue* q = malloc(sizeof(Queue));

	q->first = initNode(0);
	q->last = q->first;
	q->num_elements = 0;

	return q;
}

void push(Queue* q, unsigned long long to_insert) {
	if (q->num_elements == 0) {
		q->last->val = to_insert;
		q->num_elements++;
	}
	else {
		List* to_append = initNode(to_insert);
		q->last->next = to_append;
		q->last = to_append;
		q->num_elements++;
	}
}

unsigned long long top(Queue* q) {
	return q->first->val;
}
