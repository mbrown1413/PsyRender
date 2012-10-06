
#include "psyrender.h"

#include <math.h>

void Vector_cross(Vector* result, const Vector* a, const Vector* b) {
    Vector tmp;
    tmp.x = a->y*b->z - a->z*b->y;
    tmp.y = a->z*b->x - a->x*b->z;
    tmp.z = a->x*b->y - a->y*b->x;

    result->x = tmp.x;
    result->y = tmp.y;
    result->z = tmp.z;
}

double Vector_mag(const Vector* v) {
    return sqrt( (v->x * v->x) + (v->y * v->y) + (v->z * v->z) );
}

void Vector_normalize(Vector* v) {
    double mag = Vector_mag(v);
    v->x /= mag;
    v->y /= mag;
    v->z /= mag;
}

void Vector_scalar_mult(Vector* result, const Vector* v, double s) {
    result->x = v->x * s;
    result->y = v->y * s;
    result->z = v->z * s;
}

double Vector_dot(const Vector* a, const Vector* b) {
    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

void Vector_add(Vector* result, const Vector* a, const Vector* b) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}

void Vector_subtract(Vector* result, const Vector* a, const Vector* b) {
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}

double Vector_dist_squared(const Vector* a, const Vector* b) {
    return (a->x - b->x) * (a->x - b->x) + \
           (a->y - b->y) * (a->y - b->y) + \
           (a->z - b->z) * (a->z - b->z);
}

void Vector_assign(Vector* result, const Vector* v) {
    result->x = v->x;
    result->y = v->y;
    result->z = v->z;
}
