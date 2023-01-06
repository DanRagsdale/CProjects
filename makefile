CC=gcc
CFLAGS=-lm

SOURCES=raytrace.c vec3.c

all: my

my: $(SOURCES)
	$(CC) -o a.out $(SOURCES) $(CFLAGS)