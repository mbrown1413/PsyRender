
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "psyrender.h"

Shape* Shape_Sphere_new(double radius) {
    Shape_Sphere* s = (Shape_Sphere*) malloc(sizeof(Shape_Sphere));
    s->func = shape_sphere_func_table;
    s->r = radius;
    return (Shape*) s;
}

//TODO: Optimize and comment.  Get rid of precision issues as described here:
//      http://wiki.cgsociety.org/index.php/Ray_Sphere_Intersection
bool Shape_Sphere_ray_intersect(const Shape* _s, const Ray* r, SurfacePoint* sp_out) {
    const Shape_Sphere* s = (Shape_Sphere*) _s;
    Point intersect;
    Vector ray_origin;

    ray_origin.x = r->o.x;
    ray_origin.y = r->o.y;
    ray_origin.z = r->o.z;

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

    if (t1 <= 10*EPSILON) {
        t = t2;
    } else if (t2 <= 10*EPSILON) {
        t = t1;
    } else {
        t = t1<t2 ? t1 : t2;
    }
    if (t <= 10*EPSILON) {
        return false;
    }

    intersect.x = r->o.x + t*r->d.x;
    intersect.y = r->o.y + t*r->d.y;
    intersect.z = r->o.z + t*r->d.z;

    if (fabs(intersect.x - r->o.x) < 10*EPSILON && \
        fabs(intersect.y - r->o.y) < 10*EPSILON && \
        fabs(intersect.z - r->o.z) < 10*EPSILON)
    {
        return false;
    }

    if(sp_out != NULL) {
        sp_out->point.x = r->o.x + t*r->d.x;
        sp_out->point.y = r->o.y + t*r->d.y;
        sp_out->point.z = r->o.z + t*r->d.z;
        sp_out->norm.x = sp_out->point.x;
        sp_out->norm.y = sp_out->point.y;
        sp_out->norm.z = sp_out->point.z;
        sp_out->u = 0;
        sp_out->v = 0;
    }

    return true;
}

bool Shape_Sphere_is_inside(const Shape* _s, const Point* p) {
    Shape_Sphere* s = (Shape_Sphere*) _s;
    return p->x*p->x + p->y*p->y + p->z*p->z  <=  s->r*s->r + EPSILON;
}

bool Shape_Sphere_is_closed(const Shape* s) {
    return true;
}
