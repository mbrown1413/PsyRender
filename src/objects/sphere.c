
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
    s->func.print = Sphere_print;
    s->func.ray_intersect = Sphere_ray_intersect;
    s->mat.color = (Color){127, 127, 127};
    return s;
}

void Sphere_print(const Object* obj) {
    const Sphere* s = (Sphere*) obj;
    printf("<Sphere x=%.2f y=%.2f z=%.2f r=%.2f>\n", s->x, s->y, s->z, s->r);
}

//TODO: Optimize and comment.  Get rid of precision issues as described here:
//      http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
bool Sphere_ray_intersect(const Object* obj, const Ray* r, Ray* normal) {
    const Sphere* s = (Sphere*) obj;

    // Convert ray into object space
    double r_x = s->x - r->ox;
    double r_y = s->y - r->oy;
    double r_z = s->z - r->oz;

    double a = DOT(r->dx, r->dy, r->dz, r->dx, r->dy, r->dz);
    double b = 2 * DOT(r_x, r_y, r_z, r->dx, r->dy, r->dz);
    double c = DOT(r_x, r_y, r_z, r_x, r_y, r_z) - (s->r * s->r);

    double det = b*b - 4*a*c;  // Determinate
    if (det < 0) {
        return false;
    }

    double t1 = ( -b + sqrt(det) ) / (2*a);
    double t2 = ( -b - sqrt(det) ) / (2*a);
    double t = t1<t2 ? t1 : t2;

    // Intersect point
    normal->ox = r->ox + t*r->dx;
    normal->oy = r->oy + t*r->dy;
    normal->oz = r->oz + t*r->dz;

    // Normal vector
    normal->dx = s->x - normal->ox;
    normal->dy = s->y - normal->oy;
    normal->dz = s->z - normal->oz;

    return true;
}
