
#ifndef _PSY_SURFACE_POINT_H
#define _PSY_SURFACE_POINT_H

typedef struct {

    // Point represented by this SurfacePoint
    Point point;

    // Normal vector at this point on the surface (not nessesarily normalized)
    Vector norm;

    // u, v texture coordinates of the shape at this point
    double u, v;

    // Object associated with this surface
    Object* obj;

} SurfacePoint;

#endif
