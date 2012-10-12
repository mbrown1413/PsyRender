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

#define Canvas_start(canvas) INTERFACE_CALL_FUNC_NO_ARGS(Canvas, start, canvas)
#define Canvas_get_next_row(canvas) INTERFACE_CALL_FUNC_NO_ARGS(Canvas, get_next_row, canvas)
#define Canvas_write_row(canvas, ...) INTERFACE_CALL_FUNC(Canvas, write_row, canvas, __VA_ARGS__)
#define Canvas_finish(canvas) INTERFACE_CALL_FUNC_NO_ARGS(Canvas, finish, canvas)
#define Canvas_free(canvas) INTERFACE_CALL_FUNC_NO_ARGS(Canvas, free, canvas)

#include "canvases/png.h"
#include "canvases/mem.h"

#endif
