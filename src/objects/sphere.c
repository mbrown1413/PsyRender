
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
    s->mat = Material_default();
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

    //TODO
    if (fabs(sqrt(DIST_SQ(r->ox, r->oy, r->oz, s->x, s->y, s->z)) - s->r) < 0.1) {
        return false;
    }

    // Convert ray into object space
    double r_x = r->ox - s->x;
    double r_y = r->oy - s->y;
    double r_z = r->oz - s->z;

    double a = DOT(r->dx, r->dy, r->dz, r->dx, r->dy, r->dz);
    double b = 2 * DOT(r_x, r_y, r_z, r->dx, r->dy, r->dz);
    double c = DOT(r_x, r_y, r_z, r_x, r_y, r_z) - (s->r * s->r);

    double det = b*b - 4*a*c;  // Determinate
    if (det < 0) {
        return false;
    }

    double t1 = ( -b + sqrt(det) ) / (2*a);
    double t2 = ( -b - sqrt(det) ) / (2*a);
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
    normal->ox = r->ox + t*r->dx;
    normal->oy = r->oy + t*r->dy;
    normal->oz = r->oz + t*r->dz;

    // Normal vector
    normal->dx = s->x - normal->ox;
    normal->dy = s->y - normal->oy;
    normal->dz = s->z - normal->oz;

    return true;
}
