
#ifndef _RAY_OBJ_SPHERE_H
#define _RAY_OBJ_SPHERE_H

typedef struct {
    OBJECT_HEADER
    Point pos;
    double r;
} Sphere;

Sphere* Sphere_new(double x, double y, double z, double radius);
void Sphere_print(const Object* obj);
bool Sphere_ray_intersect(const Object* obj, const Ray* r, Point* intersect);
void Sphere_normal(const Object* obj, const Point* intersect, Vector* normal);

#endif
