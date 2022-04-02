#include "queue.h"
#include <stdlib.h>
#include <stddef.h>

List* initNode(uint64_t val, uint64_t depth) {
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

	q->first = initNode(0, 0);
	q->last = q->first;
	q->num_elements = 0;

	return q;
}

void push(Queue* q, uint64_t to_insert_val, uint64_t depth) {
	if (q->num_elements == 0) {
		q->last->val = to_insert_val;
        q->last->depth = depth;
		q->num_elements++;
	}
	else {
		List* to_append = initNode(to_insert_val, depth);
		q->last->next = to_append;
		q->last = to_append;
		q->num_elements++;
	}
}

List* top(Queue* q) {
	return q->first;
}

List* pop(Queue* q) {
	List* to_return = q->first;
	List* second = q->first->next;
//	deleteNode(q->first);
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
