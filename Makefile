CC=gcc

CFLAGS=-Wall -g

ALL=stack reverse_string

all: $(ALL)

program1: stack.c
	$(CC) $(CFLAGS) stack.c -o stack

program2: reverse_string.c
	$(CC) $(CFLAGS) reverse_string.c -o reverse_string

clean:
	rm -f $(ALL)

