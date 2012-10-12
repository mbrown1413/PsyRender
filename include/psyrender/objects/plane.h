
#ifndef _PSY_OBJ_PLANE_H
#define _PSY_OBJ_PLANE_H

typedef struct {
    OBJECT_HEADER
    Vector norm;
    Point point;
} Object_Plane;

Object* Object_Plane_new(double z);
bool Object_Plane_ray_intersect(const Object* obj, const Ray* r, Point* intersect);
void Object_Plane_normal(const Object* obj, const Point* intersect, Vector* normal);
bool Object_Plane_inside(const Object* obj, const Point* point);

#endif
