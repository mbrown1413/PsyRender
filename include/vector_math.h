
#ifndef _RAY_VECTOR_MATH_H
#define _RAY_VECTOR_MATH_H

#define DOT(x1,y1,z1, x2,y2,z2) ( (x1)*(x2) + (y1)*(y2) + (z1)*(z2) )
#define DIST_SQ(x1,y1,z1, x2,y2,z2) ( ((x1)-(x2))*((x1)-(x2)) + ((y1)-(y2))*((y1)-(y2)) + ((z1)-(z2))*((z1)-(z2)) )

void ray_reflect(
        const Ray* r,
        const Point* intersect,
        const Vector* norm,
        Ray* result);

#endif
