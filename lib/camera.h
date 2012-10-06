/**
 * A camera defines the location and projection of the image.  It maps two
 * floating point coordinates (x and y both from 0-1) to a ray.
 *
 * .. todo:: Object interface
 */

#ifndef _RAY_CAMERA_H
#define _RAY_CAMERA_H

#define CAMERA_HEADER \
    struct camera_func_table func; \
    Point pos;

struct camera_func_table {
    void (*map)(const struct Camera_struct* cam, double x, double y, Ray* r);
};

struct Camera_struct {
    CAMERA_HEADER
};

#define Camera_map(cam, x, y, r) (cam)->func.map((Camera*) cam, x, y, r)
#define Camera_free(cam) free(cam)

#include "cameras/basic.h"

#endif
