
#ifndef _RAY_OBJ_PLANE_H
#define _RAY_OBJ_PLANE_H

typedef struct {
    OBJECT_HEADER
    Vector norm;
    Point point;
} Plane;

Plane* Plane_new(double z);
bool Plane_ray_intersect(const Object* obj, const Ray* r, Point* intersect);
void Plane_normal(const Object* obj, const Point* intersect, Vector* normal);
bool Plane_inside(const Object* obj, const Point* point);

#endif
