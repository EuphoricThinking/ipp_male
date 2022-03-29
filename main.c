#include <stdio.h>
#include "queue.h"

int main() {
	Queue* q = initQueue();
	push(q, 2);
	push(q, 6);
	push(q, 12);
	//printf("%lld\n", top(q));

	while (!isEmpty(q)) {
		unsigned long long res_top = top(q);
		unsigned long long res_pop = pop(q);
		printf("%lld, %lld\n", res_top, res_pop);
	}

	deleteQueue(q);
	return 0;
}
