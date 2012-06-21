
#ifndef _RAY_CANVASES_PNG_H
#define _RAY_CANVASES_PNG_H

#include <stdio.h>

#include <png.h>

typedef struct {
    CANVAS_HEADER
    FILE* fp;
    Color* row;
    png_structp write_ptr;
    png_infop info_ptr;
    unsigned int width;
    unsigned int height;
} Canvas_Png;

Canvas* Canvas_Png_new(const char* filename, unsigned int width, unsigned int height);
bool Canvas_Png_render(Canvas* _canvas, const Scene* scene, const Camera* cam);
void Canvas_Png_free(Canvas* canvas);

#endif
