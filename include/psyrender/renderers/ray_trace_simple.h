
#ifndef _PSY_RENDERER_RAY_TRACE_SIMPLE_H
#define _PSY_RENDERER_RAY_TRACE_SIMPLE_H

typedef struct {
    RENDERER_HEADER
    unsigned int max_depth;
} Renderer_RayTraceSimple;

Renderer* Renderer_RayTraceSimple_new(unsigned int max_depth);
bool Renderer_RayTraceSimple_render(Renderer* renderer, Scene* scene, Camera* cam, Canvas* canvas);

static const struct renderer_func_table renderer_raytracesimple_func_table = {
    *Renderer_RayTraceSimple_render
};

#endif
