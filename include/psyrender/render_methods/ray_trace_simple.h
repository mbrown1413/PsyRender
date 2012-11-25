
#ifndef _PSY_RENDER_METHOD_RAY_TRACE_SIMPLE_H
#define _PSY_RENDER_METHOD_RAY_TRACE_SIMPLE_H

typedef struct {
    RENDERMETH_HEADER
} RenderMeth_RayTraceSimple;

RenderMeth* RenderMeth_RayTraceSimple_new();
bool RenderMeth_RayTraceSimple_render(RenderMeth* meth, Scene* scene, Camera* cam, Canvas* canvas);

static const struct rendermeth_func_table rendermeth_raytracesimple_func_table = {
    *RenderMeth_RayTraceSimple_render
};

#endif
