
#include <math.h>

#include "psyrender.h"

Material* Material_Checker_new(unsigned int scale) {
    Material_Checker* m = (Material_Checker*) malloc(sizeof(Material_Checker));
    m->func = material_checker_func_table;
    m->scale = scale;
    m->diffuse = 1;
    m->ambient = 1;
    m->reflective = 0;
    m->refractive = 0;
    return (Material*) m;
}

Color Material_Checker_ray_hit(
        const Scene* scene,
        const Material* mat,
        const Ray* ray,
        Point* intersect,
        Vector* norm,
        unsigned int depth) {

    Material_Checker* m = (Material_Checker*) mat;
    if (( ((int) round(intersect->x)) / m->scale + \
          ((int) round(intersect->y)) / m->scale + \
          ((int) round(intersect->z)) / m->scale) % 2)
    {
        return (Color) {0, 0, 0};
    } else {
        return (Color) {255, 255, 255};
    }
}
