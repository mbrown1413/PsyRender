
INCLUDE_DIR=include/

OBJECT_SRC=$(wildcard src/*.c src/objects/*.c)
OBJECTS=$(patsubst %.c, %.o, $(OBJECT_SRC))

INCLUDES=$(wildcard include/*.h src/objects/*.h)

CFLAGS+=-Iinclude/ --std=c99 -Werror -Wall -pedantic -lm
CFLAGS+=$(shell pkg-config libpng12 --cflags)
CFLAGS+=-g

LDFLAGS+=$(shell pkg-config libpng12 --libs)

all: main

main: $(OBJECTS) $(INCLUDES) Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -Wno-missing-prototypes $(OBJECTS) -o $@

%.o: %.c $(INCLUDES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm src/*.o src/objects/*.o main
