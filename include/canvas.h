
#ifndef _RAY_CANVAS_H
#define _RAY_CANVAS_H

#include <stdbool.h>

#define CANVAS_HEADER \
    struct canvas_func_table func; \
    char* error_str;

struct canvas_func_table {
    bool (*init)(struct Canvas_struct* canvas, const Camera* cam);
    Color* (*get_next_row)(struct Canvas_struct* canvas, const Camera* cam, unsigned int row);
    void (*finish_row)(struct Canvas_struct* canvas, Color* row);
    void (*finish)(struct Canvas_struct* canvas);
    void (*free)(struct Canvas_struct* canvas);
};

struct Canvas_struct {
    CANVAS_HEADER
};

void Canvas_set_error(Canvas* canvas, char* error);

#define Canvas_init(canvas, cam) \
    (canvas)->func.init((Canvas*) canvas, cam)
#define Canvas_get_next_row(canvas, cam, row) \
    (canvas)->func.get_next_row((Canvas*) canvas, cam, row)
#define Canvas_finish_row(canvas, row) \
    (canvas)->func.finish_row((Canvas*) canvas, row)
#define Canvas_finish(canvas) \
    (canvas)->func.finish((Canvas*) canvas)
#define Canvas_free(canvas) (canvas)->func.free((Canvas*) canvas)

#include "canvases/png.h"
#include "canvases/mem.h"

#endif
