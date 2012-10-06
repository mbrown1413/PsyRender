/**
 * .. todo:: Document Ray
 */

#ifndef _PSY_RAY_H
#define _PSY_RAY_H

typedef struct {
    Point o;  // Origin
    Vector d;  // Direction
} Ray;

void ray_reflect(
        Ray* result,
        const Ray* r,
        const Point* intersect,
        const Vector* norm);

#endif
