
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

    if (m->reflectivity) {
        Ray reflected;
        reflected.ox = norm->ox;
        reflected.oy = norm->oy;
        reflected.oz = norm->oz;
        double dot_norm_ray = DOT(norm->dx, norm->dy, norm->dz, ray->dx, ray->dy, ray->dz);
        double norm_mag_squared = norm->dx*norm->dx + norm->dy*norm->dy + norm->dz*norm->dz;
        double double_proj_mag = 2 * dot_norm_ray / norm_mag_squared;
        reflected.dx = ray->dx - double_proj_mag*norm->dx;
        reflected.dy = ray->dy - double_proj_mag*norm->dy;
        reflected.dz = ray->dz - double_proj_mag*norm->dz;

        Color reflected_color = trace_ray(scene, &reflected, depth);
        return (Color) {
            (1-m->reflectivity)*m->color.r + m->reflectivity*reflected_color.r,
            (1-m->reflectivity)*m->color.g + m->reflectivity*reflected_color.g,
            (1-m->reflectivity)*m->color.b + m->reflectivity*reflected_color.b
        };
    }

    return m->color;
}
