/**
 * A camera defines the location and projection of the image. It maps two
 * floating point coordinates (x and y both from 0-1) to a ray.
 *
 * .. todo:: Object interface
 */

#ifndef _PSY_CAMERA_H
#define _PSY_CAMERA_H

#define CAMERA_HEADER \
    struct camera_func_table func; \
    Point pos;

struct camera_func_table {
    void (*map)(const Camera* cam, double x, double y, Ray* r);
};

struct Camera_struct {
    CAMERA_HEADER
};

#define Camera_map(...) INTERFACE_CALL_FUNC(Camera, map, __VA_ARGS__)
#define Camera_free(cam) free(cam)

#include "cameras/basic.h"

#endif
