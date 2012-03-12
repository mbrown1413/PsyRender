
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "ray.h"

Sphere* Sphere_new(double x, double y, double z, double radius) {
    Sphere* s = (Sphere*) malloc(sizeof(Sphere));
    s->pos = (Point) {x, y, z};
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
    Vector ray_origin;

    Vector_subtract(&ray_origin, &r->o, &s->pos);

    double a = Vector_mag(&r->d) * Vector_mag(&r->d);
    double b = -2 * Vector_dot(&ray_origin, &r->d);
    double c = Vector_mag(&ray_origin) * Vector_mag(&ray_origin) - (s->r * s->r);

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
    if (t < EPSILON) {
        return false;
    }

    // Intersect point
    intersect->x = r->o.x + t*r->d.x;
    intersect->y = r->o.y + t*r->d.y;
    intersect->z = r->o.z + t*r->d.z;

    return true;
}

void Sphere_normal(const Object* obj, const Point* intersect, Vector* normal) {
    Sphere* s = (Sphere*) obj;
    Vector_subtract(normal, intersect, &s->pos);
}
