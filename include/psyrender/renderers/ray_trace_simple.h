
#ifndef _PSY_RENDERER_RAY_TRACE_SIMPLE_H
#define _PSY_RENDERER_RAY_TRACE_SIMPLE_H

typedef struct {
    RENDERER_HEADER
} Renderer_RayTraceSimple;

Renderer* Renderer_RayTraceSimple_new();
bool Renderer_RayTraceSimple_render(Renderer* renderer, Scene* scene, Camera* cam, Canvas* canvas);

static const struct renderer_func_table renderer_raytracesimple_func_table = {
    *Renderer_RayTraceSimple_render
};

#endif
