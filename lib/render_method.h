/**
 * .. todo:: Render Method Documentation
 */

#ifndef _RAY_RENDER_METHOD_H
#define _RAY_RENDER_METHOD_H

#define RENDERMETH_HEADER \
    struct render_meth_func_table func;

struct render_meth_func_table {
    bool (*render)(RenderMeth* meth, Scene* scene, Camera* camera, Canvas* canvas);
};

struct RenderMeth_struct {
    RENDERMETH_HEADER
};

#define RenderMeth_render(r, scene, cam, canvas) r->func.render((RenderMeth*) r, scene, cam, canvas)

#include "render_methods/ray_trace_simple.h"

#endif
