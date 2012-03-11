
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "ray.h"

Sphere* Sphere_new(double x, double y, double z, double radius) {
    Sphere* s = (Sphere*) malloc(sizeof(Sphere));
    s->x = x;
    s->y = y;
    s->z = z;
    s->r = radius;
    s->func.ray_intersect = Sphere_ray_intersect;
    s->func.normal = Sphere_normal;
    s->mat = Material_new_default();
    return s;
}

//TODO: Optimize and comment.  Get rid of precision issues as described here:
//      http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
bool Sphere_ray_intersect(const Object* obj, const Ray* r, Point* intersect) {
    const Sphere* s = (Sphere*) obj;

    // Convert ray into object space
    double r_x = r->ox - s->x;
    double r_y = r->oy - s->y;
    double r_z = r->oz - s->z;

    double a = DOT(r->dx, r->dy, r->dz, r->dx, r->dy, r->dz);
    double b = -2 * DOT(r_x, r_y, r_z, r->dx, r->dy, r->dz);
    double c = DOT(r_x, r_y, r_z, r_x, r_y, r_z) - (s->r * s->r);

    double det = b*b - 4*a*c;  // Determinate
    if (det < 0) {
        return false;
    }

    double t1 = ( b + sqrt(det) ) / (2*a);
    double t2 = ( b - sqrt(det) ) / (2*a);
    double t;
    if (t1 <= 0) {
        t = t2;
    } else if (t2 <= 0) {
        t = t1;
    } else {
        t = t1<t2 ? t1 : t2;
    }
    if (t <= 0) {
        return false;
    }

    // Intersect point
    intersect->x = r->ox + t*r->dx;
    intersect->y = r->oy + t*r->dy;
    intersect->z = r->oz + t*r->dz;

    return true;
}

void Sphere_normal(const Object* obj, const Point* intersect, Vector* normal) {
    Sphere* s = (Sphere*) obj;
    normal->x = intersect->x - s->x;
    normal->y = intersect->y - s->y;
    normal->z = intersect->z - s->z;
}
