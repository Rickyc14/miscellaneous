CC=gcc

CFLAGS=-Wall -g

ALL=stack reverse_string

all: $(ALL)

stack: stack.c
	$(CC) $(CFLAGS) stack.c -o stack

reverse_string: reverse_string.c
	$(CC) $(CFLAGS) reverse_string.c -o reverse_string

clean:
	rm -f $(ALL)

