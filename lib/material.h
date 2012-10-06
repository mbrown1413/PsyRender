/**
 * .. todo:: Material Documentation
 */

#ifndef _RAY_MATERIAL_H
#define _RAY_MATERIAL_H

#define MATERIAL_HEADER \
    struct material_func_table func; \
    double diffuse; \
    double ambient; \
    double reflective; \
    double refractive;

struct material_func_table {
    Color (*ray_hit)(const Scene* scene,
                     const struct Material_struct* mat,
                     const Ray* ray,
                     Point* intersect,
                     Vector* norm,
                     unsigned int depth);
};

struct Material_struct {
    MATERIAL_HEADER
};

Material* Material_new_default();

#define Material_ray_hit(scene, m, ray, intersect, norm, depth) \
        (m)->func.ray_hit(scene, (Material*)m, ray, intersect, norm, depth)
#define Material_free(m) free(m)

#include "materials/solid.h"
#include "materials/checker.h"

#endif
