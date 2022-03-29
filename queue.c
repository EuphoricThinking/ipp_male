#include "queue.h"
#include <stdlib.h>
#include <stddef.h>

List* initNode(unsigned long long val) {
	List* l = malloc(sizeof(List));

	l->next = NULL;
	l->val = val;

	return l;
}

void deleteNode(List* l) {
	l->next = NULL;
	free(l);
}

void deleteNodesAll(List* l) {
	if (l) {
		deleteNodesAll(l->next);
		deleteNode(l);
	}
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

unsigned long long pop(Queue* q) {
	int to_return = q->first->val;
	List* second = q->first->next;
	deleteNode(q->first);
	q->first = second;
	q->num_elements--;

	return to_return;
}

void deleteQueue(Queue* q) {
	deleteNodesAll(q->first);
	free(q);
}

bool isEmpty(Queue* q) {
	return q->num_elements == 0;
}
