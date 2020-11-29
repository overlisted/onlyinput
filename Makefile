CC = gcc
CFLAGS = -I. -O1 -g -Wall
LDFLAGS =

example: example.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
run: example
	./example
	
clean:
	rm example
