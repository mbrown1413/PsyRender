/**
 * .. todo:: Document Vector
 */

#ifndef _PSY_VECTOR_H
#define _PSY_VECTOR_H

typedef struct {
    double x, y, z;
} Vector;

bool Vector_is_equal(const Vector* v1, const Vector* v2, double epsilon);
void Vector_cross(Vector* result, const Vector* a, const Vector* b);
double Vector_mag(const Vector* v);
void Vector_normalize(Vector* v);
void Vector_scalar_mult(Vector* result, const Vector* v, double s);
double Vector_dot(const Vector* a, const Vector* b);
void Vector_add(Vector* result, const Vector* a, const Vector* b);
void Vector_subtract(Vector* result, const Vector* a, const Vector* b);
double Vector_dist_squared(const Vector* a, const Vector* b);
void Vector_assign(Vector* result, const Vector* v);

#endif
