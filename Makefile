CC=gcc
CFLAGS=-std=gnu17 -ggdb -Wall -Werror -Wno-deprecated-declarations
LIBS=-lX11 -lXtst

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	-rm client server

