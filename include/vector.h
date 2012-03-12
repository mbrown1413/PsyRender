
#ifndef _RAY_VECTOR_H
#define _RAY_VECTOR_H

void ray_reflect(
        Ray* result,
        const Ray* r,
        const Point* intersect,
        const Vector* norm);

void Vector_cross(Vector* result, const Vector* a, const Vector* b);
double Vector_mag(const Vector* v);
void Vector_normalize(Vector* v);
void Vector_scalar_mult(Vector* result, const Vector* v, double s);
double Vector_dot(const Vector* a, const Vector* b);
void Vector_add(Vector* result, const Vector* a, const Vector* b);
void Vector_subtract(Vector* result, const Vector* a, const Vector* b);
double Vector_dist_squared(const Vector* a, const Vector* b);

#endif
