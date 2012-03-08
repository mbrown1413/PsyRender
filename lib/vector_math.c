
#include "ray.h"

void ray_reflect(
        const Ray* r,
        const Point* intersect,
        const Vector* norm,
        Ray* result) {

    result->ox = intersect->x;
    result->oy = intersect->y;
    result->oz = intersect->z;
    double dot_norm_ray = DOT(norm->x, norm->y, norm->z, r->dx, r->dy, r->dz);
    double norm_mag_squared = norm->x*norm->x + norm->y*norm->y + norm->z*norm->z;
    double double_proj_mag = 2 * dot_norm_ray / norm_mag_squared;
    result->dx = r->dx - double_proj_mag*norm->x;
    result->dy = r->dy - double_proj_mag*norm->y;
    result->dz = r->dz - double_proj_mag*norm->z;

}
