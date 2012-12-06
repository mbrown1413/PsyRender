/**
 * .. todo:: Renderer Documentation
 */

#ifndef _PSY_RENDERER_H
#define _PSY_RENDERER_H

#define RENDERER_HEADER \
    struct renderer_func_table func;

struct renderer_func_table {
    bool (*render)(Renderer* renderer, Scene* scene, Camera* camera, Canvas* canvas);
};

struct Renderer_struct {
    RENDERER_HEADER
};

#define Renderer_render(...) INTERFACE_CALL_FUNC(Renderer, render, __VA_ARGS__)

#include "renderers/ray_trace_simple.h"

#endif
