
#include <math.h>

#include "ray.h"

Material* Material_Checker_new(unsigned int scale) {
    Material_Checker* m = (Material_Checker*) malloc(sizeof(Material_Checker));
    m->scale = scale;
    m->reflectivity = 0;
    m->func.ray_hit = Material_Checker_ray_hit;
    return (Material*) m;
}

Color Material_Checker_ray_hit(const Scene* scene, const Material* mat, const Ray* ray, Ray* norm, unsigned int depth) {
    //printf("%f %f %f\n", norm->ox, norm->oy, norm->oz);
    Material_Checker* m = (Material_Checker*) mat;
    if (( ((int) round(norm->ox)) / m->scale + \
          ((int) round(norm->oy)) / m->scale + \
          ((int) round(norm->oz)) / m->scale) % 2) {
        return (Color) {0, 0, 0};
    } else {
        return (Color) {255, 255, 255};
    }
}
