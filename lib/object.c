
#include <stdlib.h>

#include "psyrender.h"

Object* Object_new(Shape* shape, Material* material, Volume* volume) {
    Object* o = malloc(sizeof(Object));
    o->shape = shape;
    o->mat = material;
    o->vol = volume;
    o->trans = Transform_new();
    return o;
}

bool Object_ray_intersect(Object* o, const Ray* r, SurfacePoint* sp_out) {
    Ray r_trans;
    Transform_ray_inverse(o->trans, &r_trans, r);
    if(Shape_ray_intersect(o->shape, &r_trans, sp_out)) {
        if(sp_out != NULL) {
            Transform_point(o->trans, &sp_out->point, &sp_out->point);
            Transform_normal(o->trans, &sp_out->norm, &sp_out->norm);
            sp_out->obj = o;
        }
        return true;
    } else {
        return false;
    }
}

bool Object_is_inside(const Object* o, const Point* p) {
    Point p_trans;
    Transform_point_inverse(o->trans, &p_trans, p);
    return Shape_is_inside(o->shape, &p_trans);
}

void Object_free(Object* o) {
    Transform_free(o->trans);
    free(o);
}
