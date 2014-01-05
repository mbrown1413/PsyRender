
#ifndef _PSY_SHAPE_PLANE_H
#define _PSY_SHAPE_PLANE_H

typedef struct {
    SHAPE_HEADER
    Vector norm;
    Point point;
} Shape_Plane;

Shape* Shape_Plane_new(double z);
bool Shape_Plane_ray_intersect(const Shape* s, const Ray* r, SurfacePoint* sp_out);
bool Shape_Plane_is_inside(const Shape* s, const Point* point);
bool Shape_Plane_is_closed(const Shape* s);

static const struct shape_func_table shape_plane_func_table = {
    *Shape_Plane_ray_intersect,
    *Shape_Plane_is_inside,
    *Shape_Plane_is_closed
};

#endif
