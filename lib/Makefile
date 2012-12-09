
LIB_NAME=libpsyrender.so

LIB_CFLAGS+=-I./include/ --std=c99 -Werror -Wall -pedantic
LIB_CFLAGS+=-g
LIB_CFLAGS+=-O3
LIB_CFLAGS+=$(shell pkg-config libpng12 --cflags)

LIB_LDFLAGS+=-lm -Wl,-soname,$(LIB_NAME)
LIB_LDFLAGS+=$(shell pkg-config libpng12 --libs)

LIB_DIRS=./ objects materials canvases cameras data_structs renderers
LIB_SRC=$(foreach DIR, $(LIB_DIRS), $(wildcard $(DIR)/*.c))
LIB_OBJECTS=$(patsubst %.c, %.o, $(LIB_SRC))

INCLUDE_DIRS=$(patsubst ../lib/%, ../include/%, LIB_DIRS)
INCLUDES=$(foreach DIR, $(INCLUDE_DIRS), $(wildcard $(DIR)/*.h))


all: $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJECTS)
	$(CC) $(LIB_CFLAGS) $^ $(LIB_LDFLAGS) --shared -o $@

%.o: %.c $(INCLUDES) Makefile
	$(CC) $(LIB_CFLAGS) -I../include/ -fPIC -c $< -o $@

clean:
	-rm $(LIB_NAME)
	-rm $(LIB_OBJECTS)

.PHONY: all clean
