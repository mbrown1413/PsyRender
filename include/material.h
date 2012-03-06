
#ifndef _RAY_MATERIAL_H
#define _RAY_MATERIAL_H

#define MATERIAL_HEADER \
    struct material_func_table func;

struct Material_struct;

struct material_func_table {
    Color (*ray_hit)(const struct Material_struct* mat, Ray* ray, const Ray* norm, unsigned int depth);
};

struct Material_struct {
    MATERIAL_HEADER
};

typedef struct Material_struct Material;

Material* Material_default();

#define Material_ray_hit(m, ray, norm, depth) (m)->func.ray_hit((Material*)m, ray, norm, depth)
#define Material_free(m) free(m)

#include "materials/basic.h"

#endif
