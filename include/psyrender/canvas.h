/**
 *
 * .. c:type:: Canvas
 *
 *     .. c:member:: unsigned int width
 *     .. c:member:: unsigned int height
 *
 * .. c:function:: bool Canvas_start(Canvas* canvas)
 *
 *     Prepares the canvas to be used by resetting or initializing the state.
 *
 *     Returns true on success, false on failure.
 *
 * .. c:function:: Color* Canvas_get_next_row(Canvas* canvas)
 *
 *     Returns a row for the user to write to.  The first call returns the top
 *     row, followed by the second row, etc.  The row doesn't necessarily have
 *     to be different every time it is called, depending on how the canvas is
 *     implemented.
 *
 *     When the user is finished writing to this row,
 *     :c:func:`Canvas_write_row` should be called to write the row to the
 *     canvas.
 *
 * .. c:function:: bool Canvas_write_row(Canvas* canvas, Color* row)
 *
 *     .. todo:: Canvas_write_row
 *
 * .. c:function:: bool Canvas_finish(Canvas* canvas)
 *
 *     .. todo:: Canvas_finish
 *
 * .. c:function:: void Canvas_free(Canvas* canvas)
 *
 *     .. todo:: Canvas_free
 *
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
