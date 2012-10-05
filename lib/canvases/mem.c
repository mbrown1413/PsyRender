
#include <stdio.h>

#include "ray.h"

Canvas* Canvas_Mem_new(unsigned int width, unsigned int height) {
    Canvas_Mem* canvas = (Canvas_Mem*) malloc(sizeof(Canvas_Mem));
    canvas->image = NULL;
    canvas->width = width;
    canvas->height = height;
    canvas->func.start = Canvas_Mem_start;
    canvas->func.get_next_row = Canvas_Mem_get_next_row;
    canvas->func.write_row = Canvas_Mem_write_row;
    canvas->func.finish = Canvas_Mem_finish;
    canvas->func.free = Canvas_Mem_free;
    return (Canvas*) canvas;
}

bool Canvas_Mem_start(Canvas* _canvas) {
    Canvas_Mem* canvas = (Canvas_Mem*) _canvas;

    if (!canvas->image) {
        canvas->image = (Color*) malloc(sizeof(Color) * canvas->width * canvas->height);
    }
    if (!canvas->image) {
        fprintf(stderr, "Could not allocate memory for image!");
        return false;
    }

    canvas->next_row = 0;
    return true;
}

Color* Canvas_Mem_get_next_row(Canvas* _canvas) {
    Canvas_Mem* canvas = (Canvas_Mem*) _canvas;
    return &canvas->image[canvas->width * canvas->next_row];
}

bool Canvas_Mem_write_row(Canvas* _canvas, Color* row) {
    // Memory was written directly, no need to write anything
    Canvas_Mem* canvas = (Canvas_Mem*) _canvas;
    canvas->next_row++;
    return true;
}

bool Canvas_Mem_finish(Canvas* canvas) {
    return true;
}

void Canvas_Mem_free(Canvas* _canvas) {
    Canvas_Mem* canvas = (Canvas_Mem*) _canvas;
    if (canvas->image) {
        free(canvas->image);
    }
    free(canvas);
}
