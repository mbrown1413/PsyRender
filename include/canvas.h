/**
 * Canvas
 *
 * A canvas contains the properties of an image such as width and height, and
 * handles writing the image to some medium such as a png file.
 */

#ifndef _RAY_CANVAS_H
#define _RAY_CANVAS_H

#include <stdbool.h>

#define CANVAS_HEADER \
    struct canvas_func_table func; \
    char* error_str;

struct canvas_func_table {
    bool (*render)(Canvas* canvas, const Scene* scene, const Camera* cam);
    void (*free)(Canvas* canvas);
};

struct Canvas_struct {
    CANVAS_HEADER
};

void Canvas_set_error(Canvas* canvas, char* error);

#define Canvas_render(canvas, scene, cam) (canvas)->func.render((Canvas*) canvas, scene, cam)
#define Canvas_free(canvas) (canvas)->func.free((Canvas*) canvas)

#include "canvases/png.h"
#include "canvases/mem.h"

#endif
