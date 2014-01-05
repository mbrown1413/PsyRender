
#include <stdio.h>
#include <stdlib.h>

#include "psyrender.h"

Shape* Shape_Plane_new(double z) {
    Shape_Plane* p = (Shape_Plane*) malloc(sizeof(Shape_Plane));
    p->func = shape_plane_func_table;
    p->point = (Point) {0, 0, z};
    p->norm = (Vector) {0, 0, 1};
    return (Shape*) p;
}

bool Shape_Plane_ray_intersect(const Shape* s, const Ray* r, SurfacePoint* sp_out) {
    Shape_Plane* p = (Shape_Plane*) s;
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

    if(sp_out != NULL) {
        sp_out->point.x = r->o.x + t*r->d.x;
        sp_out->point.y = r->o.y + t*r->d.y;
        sp_out->point.z = r->o.z + t*r->d.z;
        sp_out->norm.x = 0;
        sp_out->norm.y = 0;
        sp_out->norm.z = 1;
        sp_out->u = 0;
        sp_out->v = 0;
    }

    return true;
}

bool Shape_Plane_is_inside(const Shape* s, const Point* point) {
    return false;
}

bool Shape_Plane_is_closed(const Shape* s) {
    return false;
}
