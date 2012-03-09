
#ifndef _RAY_CAMERA_H
#define _RAY_CAMERA_H

#define CAMERA_HEADER \
    struct camera_func_table func; \
    unsigned int image_height; \
    unsigned int image_width; \
    Point pos;

struct camera_func_table {
    void (*render)(const Scene* scene, const struct Camera_struct* cam, Canvas* canvas);
};

struct Camera_struct {
    CAMERA_HEADER
};

#define Camera_render(scene, cam, canvas) (cam)->func.render(scene, (Camera*)cam, canvas)
#define Camera_free(cam) free(cam)

#include "cameras/basic.h"

#endif
