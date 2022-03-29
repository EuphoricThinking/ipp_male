CC	= gcc
CFLAGS	= -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2

.PHONY: all clean

all: main

main: main.o queue.o
queue.o: queue.h
main.o: queue.h

clean:
	rm -f *.o main

run:
	./main
