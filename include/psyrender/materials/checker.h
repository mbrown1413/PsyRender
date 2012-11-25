
#ifndef _PSY_MATERIAL_CHECKER_H
#define _PSY_MATERIAL_CHECKER_H

typedef struct {
    MATERIAL_HEADER
    unsigned int scale;
} Material_Checker;

Material* Material_Checker_new(unsigned int scale);
Color Material_Checker_ray_hit(
        const Scene* scene,
        const Material* mat,
        const Ray* ray,
        Point* intersect,
        Vector* norm,
        unsigned int depth);

static const struct material_func_table material_checker_func_table = {
    *Material_Checker_ray_hit
};

#endif
