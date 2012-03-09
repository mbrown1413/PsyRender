
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
} Canvas_Png;

Canvas* Canvas_Png_new(const char* filename);
bool Canvas_Png_init(Canvas* canvas, const Camera* cam);
Color* Canvas_Png_get_next_row(Canvas* canvas);
void Canvas_Png_finish_row(Canvas* canvas, Color* row);
void Canvas_Png_finish(Canvas* canvas);

#endif
