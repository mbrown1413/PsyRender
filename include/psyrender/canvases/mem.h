
#ifndef _PSY_CANVAS_MEM
#define _PSY_CANVAS_MEM

typedef struct {
    CANVAS_HEADER
    Color* image;
    unsigned int next_row;
} Canvas_Mem;

Canvas* Canvas_Mem_new(unsigned int width, unsigned int height);
bool Canvas_Mem_start(Canvas* canvas);
Color* Canvas_Mem_get_next_row(Canvas* _canvas);
bool Canvas_Mem_write_row(Canvas* canvas, Color* row);
bool Canvas_Mem_finish(Canvas* canvas);
void Canvas_Mem_free(Canvas* canvas);

static const struct canvas_func_table canvas_mem_func_table = {
    *Canvas_Mem_start,
    *Canvas_Mem_get_next_row,
    *Canvas_Mem_write_row,
    *Canvas_Mem_finish,
    *Canvas_Mem_free
};

#endif
