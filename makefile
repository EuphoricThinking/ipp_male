CC	= gcc
CFLAGS	= -Wall -Wextra -Wno-implicit-fallthrough -std=c17 -O2

.PHONY: all clean

all: main

main: main.o queue.o input_utils.o err.o bit_lab_utils.o labirynth.o

queue.o: queue.c queue.h

main.o: main.c queue.h input_utils.h

err.o: err.c err.h

input_utils.o: input_utils.c input_utils.h err.h bit_lab_utils.h labirynth.h

bit_lab_utils.o: bit_lab_utils.c bit_lab_utils.h

labirynth.o: labirynth.c labirynth.h bit_lab_utils.h err.h

clean:
	rm -f *.o main

run:
	./main
