#include <stdio.h>
#include "queue.h"

int main() {
	Queue* q = initQueue();
	push(q, 2);
	printf("%lld\n", top(q));
	return 0;
}
