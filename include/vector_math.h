
#ifndef _RAY_VECTOR_MATH_H
#define _RAY_VECTOR_MATH_H

#define DOT(x1,y1,z1, x2,y2,z2) ( (x1)*(x2) + (y1)*(y2) + (z1)*(z2) )
#define DIST_SQ(x1,y1,z1, x2,y2,z2) ( ((x1)-(x2))*((x1)-(x2)) + ((y1)-(y2))*((y1)-(y2)) + ((z1)-(z2))*((z1)-(z2)) )

void ray_reflect(
        Ray* result,
        const Ray* r,
        const Point* intersect,
        const Vector* norm);
void vec_cross(Vector* result, const Vector* a, const Vector* b);
double vec_mag(const Vector* v);
void vec_normalize(Vector* v);
void vec_scalar_mult(Vector* result, const Vector* v, double s);

#endif
