
#ifndef _RAY_OBJ_INFCHECKER_H
#define _RAY_OBJ_INFCHECKER_H

typedef struct {
    OBJECT_HEADER
    double z;
} Plane;

Plane* Plane_new(double z);
void Plane_print(const Object* obj);
bool Plane_ray_intersect(
        const Object* obj,
        const Ray* r,
        Point* intersect,
        Vector* normal);

#endif
