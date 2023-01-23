CC=gcc
CFLAGS=-lm

SOURCES=raytrace.c vec3.c ray.c util.c

all: my

my: $(SOURCES)
	$(CC) -o a.out $(SOURCES) $(CFLAGS)