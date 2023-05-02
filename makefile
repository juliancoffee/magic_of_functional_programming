CC=gcc
CFLAGS=-Wall -Wextra

all:
	$(CC) main.c $(CFLAGS) -o main
	$(CC) closure.c $(CFLAGS) -o closure

clean:
	rm -f main closure
