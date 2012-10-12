
#ifndef _PSY_OBJ_SPHERE_H
#define _PSY_OBJ_SPHERE_H

typedef struct {
    OBJECT_HEADER
    Point pos;
    double r;
} Object_Sphere;

Object* Object_Sphere_new(double x, double y, double z, double radius);
void Object_Sphere_print(const Object* obj);
bool Object_Sphere_ray_intersect(const Object* obj, const Ray* r, Point* intersect);
void Object_Sphere_normal(const Object* obj, const Point* intersect, Vector* normal);
bool Object_Sphere_inside(const Object* obj, const Point* point);

#endif
