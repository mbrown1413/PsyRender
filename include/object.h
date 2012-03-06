
#ifndef _RAY_OBJECT_H
#define _RAY_OBJECT_H

#include <stdbool.h>

#define OBJECT_HEADER \
    struct func_table func; \
    Material mat;

struct Object_struct;

struct func_table {
    void (*print)(const struct Object_struct* obj);
    bool (*ray_intersect)(const struct Object_struct* obj, const Ray* ray, Ray* normal);
};

struct Object_struct {
    OBJECT_HEADER
};

typedef struct Object_struct Object;

#define Object_print(o) (o)->func.print((Object*)o)
#define Object_ray_intersect(o, ray, norm) (o)->func.ray_intersect((Object*)o, ray, norm)
#define Object_free(o) free(o)

#include "objects/sphere.h"
#include "objects/plane.h"

#endif
