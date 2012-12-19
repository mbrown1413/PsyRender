
CFLAGS+=-I./include/ --std=c99 -Werror -Wall -pedantic
CFLAGS+=-g
CFLAGS+=-O3

LDFLAGS=-lm -Llib/ -lpsyrender

PROGRAM_SRC=$(wildcard src/*.c)
PROGRAM_EXEC=$(patsubst src/%.c, bin/%, $(PROGRAM_SRC))


all: bin/ lib/libpsyrender.so $(PROGRAM_EXEC)

bin/%: src/%.c lib/libpsyrender.so
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(shell cat $(<:%.c=%.flags) 2>/dev/null) -Wno-missing-prototypes -o $@

lib/libpsyrender.so: lib/*
	$(MAKE) -C lib/

clean:
	$(MAKE) -C lib/ clean
	-rm bin/*

bin:
	-mkdir bin/ 2>/dev/null

.PHONY: all clean src
