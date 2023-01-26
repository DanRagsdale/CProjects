CC=gcc
CFLAGS=-lm -lpthread

SOURCES=main.c

all: my

run: all
	./a.out

my: $(SOURCES)
	$(CC) -o a.out $(SOURCES) $(CFLAGS)