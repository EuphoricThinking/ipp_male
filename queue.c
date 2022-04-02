#include "queue.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

List* init_node(uint64_t val, uint64_t depth) {
	List* l = malloc(sizeof(List));

	l->next = NULL;
	l->val = val;
    l->depth = depth;

	return l;
}

void delete_node(List* l) {
	l->next = NULL;
	free(l);
}

void delete_nodes_all(List* l) {
	if (l) {
        List *child = l->next;
        List *current = l;

        while (current) {
            delete_node(current);
            current = child;
            if (child) {
                child = current->next;
            }
        }
    }
}

Queue* init_queue() {
	Queue* q = malloc(sizeof(Queue));

//	q->first = init_node(0, 0);
//	q->last = q->first;
    q->first = NULL;
    q->last = NULL;
	q->num_elements = 0;

	return q;
}

void push(Queue* q, uint64_t to_insert_val, uint64_t depth) {
//    printf("entered\n");
	if (q->num_elements == 0) {
//		q->last->val = to_insert_val;
//        q->last->depth = depth;
//		q->num_elements++;
//        q->first->val = to_insert_val;
//        q->first->depth = depth;
        q->first = init_node(to_insert_val, depth);
        q->last = q->first;
        q->num_elements++;
	}
	else {
		List* to_append = init_node(to_insert_val, depth);
		q->last->next = to_append;
		q->last = to_append;
		q->num_elements++;
	}
}

List* top(Queue* q) {
    if (q->num_elements == 0) {
        return NULL;
    }
    else {
        return q->first;
    }
}

List* pop(Queue* q) {
    if (q->num_elements > 0) {
    List *to_return = q->first;
    List *second = q->first->next;
//	deleteNode(q->first);
    q->first = second;
    q->num_elements--;

    return to_return;
    }
    else {
        return NULL;
    }
}

void delete_queue(Queue* q) {
	delete_nodes_all(q->first);
	free(q);
}

bool is_empty(Queue* q) {
	return q->num_elements == 0;
}
