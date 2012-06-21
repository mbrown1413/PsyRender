
#include <stdlib.h>

#include "ray.h"

//TODO: More options
//TODO: Alignment option
Canvas* Canvas_Mem_new() {
    Canvas_Mem* canvas = (Canvas_Mem*) malloc(sizeof(Canvas_Mem));
    canvas->image = NULL;
    canvas->func.render = Canvas_Mem_render;
    canvas->func.free = Canvas_Mem_free;
    return (Canvas*) canvas;
}

bool Canvas_Mem_render(Canvas* _canvas, const Scene* scene, const Camera* cam) {
    Canvas_Mem* canvas = (Canvas_Mem*) _canvas;
    Color* row;
    Ray ray;

    // Allocate image memory
    if (canvas->image) {
        free(canvas->image);
    }
    canvas->image = malloc(sizeof(Color) * canvas->width * canvas->height);
    if (!canvas->image) {
        Canvas_set_error(_canvas, "Could not allocate memory for image!");
        return false;
    }

    row = canvas->image;
    for (int y=canvas->height-1; y>=0; y--) {
        for (int x=0; x<canvas->width; x++) {
            Camera_map(cam, ((double)x)/canvas->width, ((double)y)/canvas->height, &ray);
            row[x] = trace_ray_priv(scene, &ray, 0, ETHER_INDEX_OF_REFRACTION);
        }
        row += canvas->width;
    }
    return true;
}

void Canvas_Mem_free(Canvas* _canvas) {
    Canvas_Mem* canvas = (Canvas_Mem*) _canvas;
    if (canvas->image) {
        free(canvas->image);
    }
    free(canvas);
}
