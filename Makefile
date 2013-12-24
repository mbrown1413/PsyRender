
##### Configuration #####

LIB_NAME=psyrender
LIB_SONAME=lib$(LIB_NAME).so

CFLAGS+=-I./include/ --std=c99 -Werror -Wall -pedantic
CFLAGS+=-g
#CFLAGS+=-O3

LIB_CFLAGS=$(CFLAGS) $(shell pkg-config libpng12 --cflags)

LDFLAGS=-L./ -l$(LIB_NAME) -lm $(shell pkg-config libpng12 --libs)

all: library programs


##### Building Library #####
# Compiles all .c files in $(LIB_DIRS) into a .so file

LIB_DIRS=lib/ lib/objects lib/materials lib/canvases lib/cameras lib/data_structs lib/renderers
LIB_SRC=$(foreach DIR, $(LIB_DIRS), $(wildcard $(DIR)/*.c))
LIB_OBJECTS=$(patsubst %.c, %.o, $(LIB_SRC))

INCLUDE_DIRS=$(patsubst lib/%, include/%, LIB_DIRS)
INCLUDES=$(foreach DIR, $(INCLUDE_DIRS), $(wildcard $(DIR)/*.h))

library: $(LIB_SONAME)

$(LIB_SONAME): $(LIB_OBJECTS)
	$(CC) $^ -Wl,-soname,$(LIB_SONAME) --shared -o $@

lib/%.o: lib/%.c $(INCLUDES)
	$(CC) $(LIB_CFLAGS) -I../include/ -fPIC -c $< -o $@


##### Building src/ Programs #####
# Compiles each .c file in src/ into a binary file in bin/

PROG_SRC=$(wildcard src/*.c)
PROG_EXEC=$(patsubst src/%.c, bin/%, $(PROG_SRC))

programs: bin $(LIB_SONAME) $(PROG_EXEC)

bin/%: src/%.c
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(shell cat $(<:%.c=%.flags) 2>/dev/null) -o $@

bin:
	-mkdir bin/ 2>/dev/null


##### Misc #####

clean:
	-rm $(LIB_SONAME)
	-rm $(LIB_OBJECTS)
	-rm bin/*

.PHONY: all clean programs
