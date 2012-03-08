
#include <stdlib.h>

#include "ray.h"

Material* Material_Basic_new() {
    Material_Basic* m = (Material_Basic*) malloc(sizeof(Material_Basic));
    m->color = (Color) {255, 255, 255};
    m->reflectivity = 0;
    m->func.ray_hit = Material_Basic_ray_hit;
    return (Material*) m;
}

Color Material_Basic_ray_hit(const Scene* scene, const Material* mat, const Ray* ray, Ray* norm, unsigned int depth) {
    Material_Basic* m = (Material_Basic*) mat;
    return m->color;
}
