
#include <stdio.h>
#include <stdlib.h>

#include "ray.h"

Plane* Plane_new(double z) {
    Plane* p = (Plane*) malloc(sizeof(Plane));
    p->z = z;
    p->func.ray_intersect = Plane_ray_intersect;
    p->func.normal = Plane_normal;
    p->mat = Material_new_default();
    return p;
}

void Plane_print(const Object* obj) {
}

bool Plane_ray_intersect(const Object* obj, const Ray* r, Point* intersect) {

    Plane* p = (Plane*) obj;
    double denominator = DOT(0, 0, 1, r->dx, r->dy, r->dz);
    if (denominator == 0.0) {
        return false;
    }
    double t = -1*DOT(0, 0, 1, r->ox, r->oy, r->oz - p->z) / denominator;
    if (t <= 0) {
        return false;
    }
    if (t <= EPSILON) {
        return false;
    }

    // Intersect point
    intersect->x = r->ox + t*r->dx;
    intersect->y = r->oy + t*r->dy;
    intersect->z = r->oz + t*r->dz;

    return true;
}

void Plane_normal(const Object* obj, const Point* intersect, Vector* normal) {
    normal->x = 0;
    normal->y = 0;
    normal->z = 1;
}
