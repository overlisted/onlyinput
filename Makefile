CC = gcc
CFLAGS = -I. -O1 -g -Wall
LDFLAGS = -lX11 -lm -lpthread -lGL

example: example.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
run: example
	./example
	
clean:
	rm example
