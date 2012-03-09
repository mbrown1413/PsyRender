
#ifndef _RAY_CANVASES_MEM_H
#define _RAY_CANVASES_MEM_H

typedef struct {
    CANVAS_HEADER
    Color* image;
    Color* current_row;
} Canvas_Mem;

Canvas* Canvas_Mem_new();
bool Canvas_Mem_init(Canvas* canvas, const Camera* cam);
Color* Canvas_Mem_get_next_row(Canvas* canvas, const Camera* cam, unsigned int row);
void Canvas_Mem_finish_row(Canvas* canvas, Color* row);
void Canvas_Mem_finish(Canvas* canvas);
void Canvas_Mem_free(Canvas* canvas);

#endif
