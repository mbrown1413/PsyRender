
PROGRAM_SRC=$(wildcard src/*.c)
PROGRAM_EXEC=$(patsubst src/%.c, bin/%, $(PROGRAM_SRC))

LIB_DIRS=lib lib/objects lib/materials lib/canvases lib/cameras lib/data_structs lib/renderers
LIB_SRC=$(foreach DIR, $(LIB_DIRS), $(wildcard $(DIR)/*.c))
LIB_OBJECTS=$(patsubst %.c, %.o, $(LIB_SRC))

INCLUDE_DIRS=$(patsubst lib/%, include/%, LIB_DIRS)
INCLUDES=$(foreach DIR, $(INCLUDE_DIRS), $(wildcard $(DIR)/*.h))

CFLAGS+=-I./include/ --std=c99 -Werror -Wall -pedantic -lm
CFLAGS+=$(shell pkg-config libpng12 --cflags)
CFLAGS+=-g
CFLAGS+=-O3

LDFLAGS+=$(shell pkg-config libpng12 --libs)


all: $(PROGRAM_EXEC)

%.o: %.c $(INCLUDES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

bin/%: src/%.c $(LIB_OBJECTS) $(INCLUDES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(shell cat $(<:%.c=%.flags) 2>/dev/null) -Wno-missing-prototypes $(LIB_OBJECTS) $< -o $@

bin/:
	-mkdir bin

clean:
	-rm $(LIB_OBJECTS)
	-rm $(PROGRAM_EXEC)

.PHONY: all clean
