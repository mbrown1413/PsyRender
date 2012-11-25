
#ifndef _PSY_CANVASES_PNG_H
#define _PSY_CANVASES_PNG_H

#include <stdio.h>

#include <png.h>

typedef struct {
    CANVAS_HEADER
    FILE* fp;
    Color* row;
    png_structp write_ptr;
    png_infop info_ptr;
} Canvas_Png;

Canvas* Canvas_Png_new(const char* filename, unsigned int width, unsigned int height);
bool Canvas_Png_start(Canvas* canvas);
Color* Canvas_Png_get_next_row(Canvas* _canvas);
bool Canvas_Png_write_row(Canvas* _canvas, Color* row);
bool Canvas_Png_finish(Canvas* _canvas);
void Canvas_Png_free(Canvas* canvas);

static const struct canvas_func_table canvas_png_func_table = {
    *Canvas_Png_start,
    *Canvas_Png_get_next_row,
    *Canvas_Png_write_row,
    *Canvas_Png_finish,
    *Canvas_Png_free
};

#endif
