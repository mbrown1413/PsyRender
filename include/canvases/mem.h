
#ifndef _RAY_CANVASES_MEM_H
#define _RAY_CANVASES_MEM_H

typedef struct {
    CANVAS_HEADER
    Color* image;
    unsigned int width;
    unsigned int height;
} Canvas_Mem;

Canvas* Canvas_Mem_new();
bool Canvas_Mem_render(Canvas* _canvas, const Scene* scene, const Camera* cam);
void Canvas_Mem_free(Canvas* canvas);

#endif
