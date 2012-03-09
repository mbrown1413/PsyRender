
#include "ray.h"

#include <math.h>

void ray_reflect(
        Ray* result,
        const Ray* r,
        const Point* intersect,
        const Vector* norm) {

    result->ox = intersect->x;
    result->oy = intersect->y;
    result->oz = intersect->z;
    double dot_norm_ray = DOT(norm->x, norm->y, norm->z, r->dx, r->dy, r->dz);
    double norm_mag_squared = norm->x*norm->x + norm->y*norm->y + norm->z*norm->z;
    double double_proj_mag = 2 * dot_norm_ray / norm_mag_squared;
    result->dx = r->dx - double_proj_mag*norm->x;
    result->dy = r->dy - double_proj_mag*norm->y;
    result->dz = r->dz - double_proj_mag*norm->z;
}

void vec_cross(Vector* result, const Vector* a, const Vector* b) {
    Vector tmp;
    tmp.x = a->y*b->z - a->z*b->y;
    tmp.y = a->z*b->x - a->x*b->z;
    tmp.z = a->x*b->y - a->y*b->x;

    result->x = tmp.x;
    result->y = tmp.y;
    result->z = tmp.z;
}

double vec_mag(const Vector* v) {
    return sqrt( (v->x * v->x) + (v->y * v->y) + (v->z * v->z) );
}

void vec_normalize(Vector* v) {
    double mag = vec_mag(v);
    v->x /= mag;
    v->y /= mag;
    v->z /= mag;
}

void vec_scalar_mult(Vector* result, const Vector* v, double s) {
    result->x = v->x * s;
    result->y = v->y * s;
    result->z = v->z * s;
}
