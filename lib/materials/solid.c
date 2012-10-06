
#include <stdlib.h>

#include "psyrender.h"

Material* Material_Solid_new() {
    Material_Solid* m = (Material_Solid*) malloc(sizeof(Material_Solid));
    m->color = (Color) {255, 255, 255};
    m->diffuse = 1;
    m->ambient = 1;
    m->reflective = 0;
    m->refractive = 0;
    m->func.ray_hit = Material_Solid_ray_hit;
    return (Material*) m;
}

Color Material_Solid_ray_hit(
        const Scene* scene,
        const Material* mat,
        const Ray* ray,
        Point* intersect,
        Vector* norm,
        unsigned int depth) {

    Material_Solid* m = (Material_Solid*) mat;
    return m->color;
}
