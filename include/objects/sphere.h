
#ifndef _RAY_OBJ_SPHERE_H
#define _RAY_OBJ_SPHERE_H

#include "ray.h"

typedef struct {
    OBJECT_HEADER
    double x, y, z, r;
} Sphere;

Sphere* Sphere_new(double x, double y, double z, double radius);
void Sphere_print(const Object* obj);
bool Sphere_ray_intersect(const Object* obj, const Ray* r, Ray* normal);

#endif
