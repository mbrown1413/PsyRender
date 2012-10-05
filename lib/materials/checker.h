
#ifndef _RAY_MATERIAL_CHECKER_H
#define _RAY_MATERIAL_CHECKER_H

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

#endif
