
#ifndef _PSY_SHAPE_H
#define _PSY_SHAPE_H

#define SHAPE_HEADER \
    struct shape_func_table func; \

struct shape_func_table {
    bool (*ray_intersect)(const Shape* s, const Ray* ray, SurfacePoint* sp_out);
    bool (*is_inside)(const Shape* s, const Point* point);
    bool (*is_closed)(const Shape* s);
    //void (*bounding_box)(const Shape* s, const Transform* t, BoundingBox* out);
};

struct Shape_struct {
    SHAPE_HEADER
};

/**
 * Returns true if the ray intersects with the shape, false otherwise.
 *
 * If ``sp_out`` is not NULL, then the ``point``, ``normal``, ``u`` and ``v``
 * attributes of ``sp_out`` are filled in with the correct information for the
 * closest intersection found. Otherwise, ``sp_out`` remains untouched.
*/
#define Shape_ray_intersect(...) INTERFACE_CALL_FUNC(Shape, ray_intersect, __VA_ARGS__)

/**
 * Return true if the point is inside the shape, false otherwise.
 */
#define Shape_is_inside(...) INTERFACE_CALL_FUNC(Shape, is_inside, __VA_ARGS__)

/**
 * Return true if the shape completely encloses a volume.
 *
 * If the shape is not closed, objects with this shape cannot have a volume.
 */
#define Shape_is_closed(...) INTERFACE_CALL_FUNC(Shape, is_closed, __VA_ARGS__)

/**
 * Calculate the axis-aligned bounding box of shape ``s`` in world coordinates.
 *
 * A world to shape transform is given, use the ``Transform_*_inverse()``
 * functions to convert from shape to world coordinates.
 */
//#define Shape_bounding_box(...) INTERFACE_CALL_FUNC(Shape, bounding_box, __VA_ARGS__)

#include "shapes/sphere.h"
#include "shapes/plane.h"

#endif
