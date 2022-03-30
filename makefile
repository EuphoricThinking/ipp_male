CC	= gcc
CFLAGS	= -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2

.PHONY: all clean

all: main

main: main.o queue.o input_utils.o
queue.o: queue.h
main.o: queue.h

err.o: err.h

input_utils.o: input_utils.h err.h labirynt_struct.h

clean:
	rm -f *.o main

run:
	./main
