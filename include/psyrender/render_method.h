/**
 * .. todo:: Render Method Documentation
 */

#ifndef _PSY_RENDER_METHOD_H
#define _PSY_RENDER_METHOD_H

#define RENDERMETH_HEADER \
    struct rendermeth_func_table func;

struct rendermeth_func_table {
    bool (*render)(RenderMeth* meth, Scene* scene, Camera* camera, Canvas* canvas);
};

struct RenderMeth_struct {
    RENDERMETH_HEADER
};

#define RenderMeth_render(...) INTERFACE_CALL_FUNC(RenderMeth, render, __VA_ARGS__)

#include "render_methods/ray_trace_simple.h"

#endif
