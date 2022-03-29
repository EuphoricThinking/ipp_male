#include <stdio.h>
#include "queue.h"

int main() {
	Queue* q = initQueue();
	push(q, 2);
	push(q, 6);
	push(q, 12);
	printf("%lld\n", top(q));
	return 0;
}
