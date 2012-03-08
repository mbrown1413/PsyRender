
#include <math.h>

#include "ray.h"

Material* Material_Checker_new(unsigned int scale) {
    Material_Checker* m = (Material_Checker*) malloc(sizeof(Material_Checker));
    m->scale = scale;
    m->reflectivity = 0;
    m->func.ray_hit = Material_Checker_ray_hit;
    return (Material*) m;
}

Color Material_Checker_ray_hit(
        const Scene* scene,
        const Material* mat,
        const Ray* ray,
        Point* intersect,
        Vector* norm,
        unsigned int depth) {

    //printf("%f %f %f\n", norm->ox, norm->oy, norm->oz);
    Material_Checker* m = (Material_Checker*) mat;
    if (( ((int) round(intersect->x)) / m->scale + \
          ((int) round(intersect->y)) / m->scale + \
          ((int) round(intersect->z)) / m->scale) % 2) {
        return (Color) {0, 0, 0};
    } else {
        return (Color) {255, 255, 255};
    }
}
