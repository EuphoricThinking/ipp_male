CC	= gcc
CFLAGS	= -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2

.PHONY: all clean

all: labyrinth

labyrinth: main.o err.o input_utils.o bit_lab_utils.o labyrinth.o queue.o

queue.o: queue.c queue.h

main.o: main.c queue.h input_utils.h bit_lab_utils.h

err.o: err.c err.h

input_utils.o: input_utils.c input_utils.h err.h bit_lab_utils.h labyrinth.h

bit_lab_utils.o: bit_lab_utils.c bit_lab_utils.h

labyrinth.o: labyrinth.c labyrinth.h bit_lab_utils.h err.h

clean:
	rm -f *.o labyrinth

run:
	./labyrinth < ./example_tests/error00.in
