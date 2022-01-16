CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall -Werror
LIBS=-lX11

all: main

main: main.c
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	-rm *.o main

