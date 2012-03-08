
INCLUDE_DIR=include/

PROGRAM_SRC=$(wildcard src/*.c)
PROGRAM_EXEC=$(patsubst src/%.c, bin/%, $(PROGRAM_SRC))

OBJECT_SRC=$(wildcard lib/*.c lib/objects/*.c lib/materials/*.c)
OBJECTS=$(patsubst %.c, %.o, $(OBJECT_SRC))

INCLUDES=$(wildcard include/*.h include/objects/*.h include/materials/*.h)

CFLAGS+=-Iinclude/ --std=c99 -Werror -Wall -pedantic -lm
CFLAGS+=$(shell pkg-config libpng12 --cflags)
CFLAGS+=-g

LDFLAGS+=$(shell pkg-config libpng12 --libs)

all: $(PROGRAM_EXEC)

%.o: %.c $(INCLUDES) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

bin/%: src/%.c $(OBJECTS) $(INCLUDES) bin/
	$(CC) $(CFLAGS) $(LDFLAGS) -Wno-missing-prototypes $(OBJECTS) $< -o $@

bin/:
	mkdir bin

clean:
	-rm $(OBJECTS)
	-rm $(PROGRAM_EXEC)
