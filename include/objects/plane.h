
#ifndef _RAY_OBJ_INFCHECKER_H
#define _RAY_OBJ_INFCHECKER_H

#include "ray.h"

typedef struct {
    OBJECT_HEADER
    double z;
} Plane;

Plane* Plane_new(double z);
void Plane_print(const Object* obj);
bool Plane_ray_intersect(const Object* obj, const Ray* r, Ray* normal);

#endif
