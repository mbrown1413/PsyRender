
#include <stdlib.h>

#include "ray.h"

Canvas* Canvas_Mem_new() {
    Canvas_Mem* canvas = (Canvas_Mem*) malloc(sizeof(Canvas_Mem));
    canvas->func.init = Canvas_Mem_init;
    canvas->image = NULL;
    canvas->current_row = NULL;

    canvas->func.get_next_row = Canvas_Mem_get_next_row;
    canvas->func.finish_row = Canvas_Mem_finish_row;
    canvas->func.finish = Canvas_Mem_finish;
    canvas->func.free = Canvas_Mem_free;
    return (Canvas*) canvas;
}

bool Canvas_Mem_init(Canvas* canvas, const Camera* cam) {
    Canvas_Mem* mem_canvas = (Canvas_Mem*) canvas;
    if (mem_canvas->image) {
        free(mem_canvas->image);
    }
    mem_canvas->image = malloc(sizeof(Color) * cam->image_width * cam->image_height);
    if (!mem_canvas->image) {
        Canvas_set_error(canvas, "Could not allocate memory for image!");
        return false;
    }
    mem_canvas->current_row = mem_canvas->image;
    return true;
}

Color* Canvas_Mem_get_next_row(Canvas* canvas, const Camera* cam, unsigned int row) {
    Canvas_Mem* mem_canvas = (Canvas_Mem*) canvas;
    return &mem_canvas->image[row*cam->image_width];
}

void Canvas_Mem_finish_row(Canvas* canvas, Color* row) {
}

void Canvas_Mem_finish(Canvas* canvas) {
}

void Canvas_Mem_free(Canvas* canvas) {
    Canvas_Mem* mem_canvas = (Canvas_Mem*) canvas;
    if (mem_canvas->image) {
        free(mem_canvas->image);
    }
    free(mem_canvas);
}
