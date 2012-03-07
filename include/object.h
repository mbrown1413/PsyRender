
#ifndef _RAY_OBJECT_H
#define _RAY_OBJECT_H

#include <stdbool.h>
#include <stdlib.h>

#define OBJECT_HEADER \
    struct object_func_table func; \
    Material* mat;

struct object_func_table {
    void (*print)(const struct Object_struct* obj);
    bool (*ray_intersect)(const struct Object_struct* obj, const Ray* ray, Ray* normal);
};

struct Object_struct {
    OBJECT_HEADER
};

void Object_set_material(Object* obj, Material* mat);

#define Object_print(o) (o)->func.print((Object*)o)
#define Object_ray_intersect(o, ray, norm) (o)->func.ray_intersect((Object*)o, ray, norm)
#define Object_free(o) free(o)

#include "objects/sphere.h"
#include "objects/plane.h"

#endif
