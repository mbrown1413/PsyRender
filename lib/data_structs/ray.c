
#include "psyrender.h"

bool Ray_is_equal(const Ray* r1, const Ray* r2, double epsilon) {
    return Point_is_equal(&r1->o, &r2->o, epsilon) &&
           Vector_is_equal(&r1->d, &r2->d, epsilon);
}

void Ray_reflect(
        Ray* result,
        const Ray* r,
        const Point* intersect,
        const Vector* norm) {

    result->o.x = intersect->x;
    result->o.y = intersect->y;
    result->o.z = intersect->z;
    double dot_norm_ray = Vector_dot(norm, &r->d);
    double norm_mag_squared = Vector_mag(norm) * Vector_mag(norm);
    double double_proj_mag = 2 * dot_norm_ray / norm_mag_squared;
    result->d.x = r->d.x - double_proj_mag*norm->x;
    result->d.y = r->d.y - double_proj_mag*norm->y;
    result->d.z = r->d.z - double_proj_mag*norm->z;
}
