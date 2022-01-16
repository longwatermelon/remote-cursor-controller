CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall -Werror -Wno-deprecated-declarations
LIBS=-lX11

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	-rm client server

