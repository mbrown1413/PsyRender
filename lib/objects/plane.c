
#include <stdio.h>
#include <stdlib.h>

#include "psyrender.h"

Object* Object_Plane_new(double z) {
    Object_Plane* p = (Object_Plane*) malloc(sizeof(Object_Plane));
    p->point = (Point) {0, 0, z};
    p->norm = (Vector) {0, 0, 1};
    p->mat = Material_new_default();
    p->func.ray_intersect = Object_Plane_ray_intersect;
    p->func.normal = Object_Plane_normal;
    p->func.inside = Object_Plane_inside;
    return (Object*) p;
}

bool Object_Plane_ray_intersect(const Object* obj, const Ray* r, Point* intersect) {
    Object_Plane* p = (Object_Plane*) obj;
    Vector tmp_vector;

    double denominator = Vector_dot(&p->norm, &r->d);
    if (denominator == 0.0) {
        return false;
    }
    Vector_subtract(&tmp_vector, &r->o, &p->point);
    double t = -1*Vector_dot(&p->norm, &tmp_vector) / denominator;
    if (t <= 0) {
        return false;
    }
    if (t <= EPSILON) {
        return false;
    }

    // Intersect point
    intersect->x = r->o.x + t*r->d.x;
    intersect->y = r->o.y + t*r->d.y;
    intersect->z = r->o.z + t*r->d.z;

    return true;
}

void Object_Plane_normal(const Object* obj, const Point* intersect, Vector* normal) {
    normal->x = 0;
    normal->y = 0;
    normal->z = 1;
}

bool Object_Plane_inside(const Object* obj, const Point* point) {
    return true;
}
