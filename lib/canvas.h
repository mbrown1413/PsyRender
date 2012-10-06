/**
 * A canvas contains the properties of an image such as width and height, and
 * handles writing the image to some medium such as an image file.
 *
 * .. todo:: Canvas Interface
 */

#ifndef _PSY_CANVAS_H
#define _PSY_CANVAS_H

#include <stdbool.h>

#define CANVAS_HEADER \
    struct canvas_func_table func; \
    unsigned int width, height;

struct canvas_func_table {
    bool (*start)(Canvas* canvas);
    Color* (*get_next_row)(Canvas* canvas);
    bool (*write_row)(Canvas* canvas, Color* row);
    bool (*finish)(Canvas* canvas);
    void (*free)(Canvas* canvas);
};

struct Canvas_struct {
    CANVAS_HEADER
};

#define Canvas_start(canvas) (canvas)->func.start((Canvas*) canvas)
#define Canvas_get_next_row(canvas) (canvas)->func.get_next_row((Canvas*) canvas)
#define Canvas_write_row(canvas, row) (canvas)->func.write_row((Canvas*) canvas, row)
#define Canvas_finish(canvas) (canvas)->func.finish((Canvas*) canvas)
#define Canvas_free(canvas) (canvas)->func.free((Canvas*) canvas)

#include "canvases/png.h"
#include "canvases/mem.h"

#endif
