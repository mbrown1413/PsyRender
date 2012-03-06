
#include <stdio.h>
#include <stdlib.h>

#include "ray.h"

Plane* Plane_new(double z) {
    Plane* p = (Plane*) malloc(sizeof(Plane));
    p->z = z;
    p->func.print = Plane_print;
    p->func.ray_intersect = Plane_ray_intersect;
    p->mat = Material_default();
    return p;
}
void Plane_print(const Object* obj) {
}

bool Plane_ray_intersect(const Object* obj, const Ray* r, Ray* normal) {
    Plane* p = (Plane*) obj;
    double denominator = DOT(0, 0, 1, r->dx, r->dy, r->dz);
    if (denominator == 0.0) {
        return false;
    }
    double t = -DOT(0, 0, 1, r->ox, r->oy, r->oz - p->z) / denominator;
    if (t <= 0) {
        return false;
    }

    // Intersect point
    normal->ox = r->ox + t*r->dx;
    normal->oy = r->oy + t*r->dy;
    normal->oz = r->oz + t*r->dz;

    normal->dx = 0;
    normal->dy = 0;
    normal->dz = 1;

    return true;
}
