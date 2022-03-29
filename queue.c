#include "queue.h"

List* initNode(unsigned long long val) {
	List* l = malloc(sizeof(List));

	l->next = NULL;
	l->val = val;

	return l;
}

Queue* initQueue() {
	Queue* q = malloc(sizeof(queue));

	q->first = initNode(NULL);
	q->last = q->first;
	q->num_elements = 0;

	return q;
}
