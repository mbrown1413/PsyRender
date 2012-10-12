/**
 * .. todo:: Render Method Documentation
 */

#ifndef _PSY_RENDER_METHOD_H
#define _PSY_RENDER_METHOD_H

#define RENDERMETH_HEADER \
    struct render_meth_func_table func;

struct render_meth_func_table {
    bool (*render)(RenderMeth* meth, Scene* scene, Camera* camera, Canvas* canvas);
};

struct RenderMeth_struct {
    RENDERMETH_HEADER
};

#define RenderMeth_render(...) INTERFACE_CALL_FUNC(RenderMeth, render, __VA_ARGS__)

#include "render_methods/ray_trace_simple.h"

#endif
