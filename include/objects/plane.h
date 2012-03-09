
#ifndef _RAY_OBJ_PLANE_H
#define _RAY_OBJ_PLANE_H

typedef struct {
    OBJECT_HEADER
    double z;
} Plane;

Plane* Plane_new(double z);
void Plane_print(const Object* obj);
bool Plane_ray_intersect(const Object* obj, const Ray* r, Point* intersect);
void Plane_normal(const Object* obj, const Point* intersect, Vector* normal);

#endif
