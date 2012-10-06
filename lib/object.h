/**
 * A physical object that can be rendered.
 *
 * .. todo:: Object interface
 */

#ifndef _PSY_OBJECT_H
#define _PSY_OBJECT_H

#include <stdbool.h>
#include <stdlib.h>

#define OBJECT_HEADER \
    struct object_func_table func; \
    Material* mat;

struct object_func_table {
    bool (*ray_intersect)(const struct Object_struct* obj, const Ray* ray, Point* intersect);
    void (*normal)(const struct Object_struct* obj, const Point* intersect, Vector* normal);
    bool (*inside)(const struct Object_struct* obj, const Point* point);
};

struct Object_struct {
    OBJECT_HEADER
};

void Object_set_material(Object* obj, Material* mat);
void Object_free(Object* obj);

#define Object_ray_intersect(o, ray, intersect) \
        (o)->func.ray_intersect((Object*)o, ray, intersect)
#define Object_normal(o, intersect, norm) \
        (o)->func.normal((Object*)o, intersect, norm)
#define Object_inside(o, point) \
        (o)->func.inside(o, point)

#include "objects/sphere.h"
#include "objects/plane.h"

#endif
