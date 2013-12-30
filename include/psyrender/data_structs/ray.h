/**
 * .. todo:: Document Ray
 */

#ifndef _PSY_RAY_H
#define _PSY_RAY_H

typedef struct {
    Point o;  // Origin
    Vector d;  // Direction
} Ray;

void Ray_reflect(
        Ray* result,
        const Ray* r,
        const Point* intersect,
        const Vector* norm);

bool Ray_is_equal(const Ray* r1, const Ray* r2, double epsilon);

#endif
