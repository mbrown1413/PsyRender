
#ifndef _PSY_SHAPE_SPHERE_H
#define _PSY_SHAPE_SPHERE_H

typedef struct {
    SHAPE_HEADER
    double r;
} Shape_Sphere;

Shape* Shape_Sphere_new(double radius);
bool Shape_Sphere_ray_intersect(const Shape* s, const Ray* r, SurfacePoint* sp_out);
bool Shape_Sphere_is_inside(const Shape* s, const Point* point);
bool Shape_Sphere_is_closed(const Shape* s);

static const struct shape_func_table shape_sphere_func_table = {
    *Shape_Sphere_ray_intersect,
    *Shape_Sphere_is_inside,
    *Shape_Sphere_is_closed
};

#endif
