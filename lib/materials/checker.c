
#include <stdlib.h>
#include <math.h>

#include "psyrender.h"

// Private Prototypes
Material* Material_Checker_get_active(const Material_Checker* m, const SurfacePoint* sp);


Material* Material_Checker_new(unsigned int scale, Material* tile1, Material* tile2) {
    Material_Checker* m = (Material_Checker*) malloc(sizeof(Material_Checker));
    m->func = material_checker_func_table;
    m->scale = scale;
    m->tile1 = tile1;
    m->tile2 = tile2;
    return (Material*) m;
}

Material* Material_Checker_get_active(const Material_Checker* m, const SurfacePoint* sp) {
    if (( ((int) round(sp->point.x)) / m->scale + \
          ((int) round(sp->point.y)) / m->scale + \
          ((int) round(sp->point.z)) / m->scale) % 2)
    {
        return m->tile1;
    } else {
        return m->tile2;
    }
}

Color Material_Checker_direction_scatter(const Material* _mat,
                                         const SurfacePoint* sp,
                                         const Photon* in,
                                         const Ray* out) {
    const Material_Checker* mat = (const Material_Checker*) _mat;
    const Material* active_mat = Material_Checker_get_active(mat, sp);
    return Material_direction_scatter(active_mat, sp, in, out);
}

PhotonList* Material_Checker_special_scatter(const Material* _mat,
                                             const SurfacePoint* sp,
                                             const Photon* in) {
    const Material_Checker* mat = (const Material_Checker*) _mat;
    const Material* active_mat = Material_Checker_get_active(mat, sp);
    return Material_special_scatter(active_mat, sp, in);
}

void Material_Checker_free(Material* mat) {
    free(mat);
}

void Material_Checker_free_with_tiles(Material* _mat) {
    Material_Checker* mat = (Material_Checker*) _mat;
    Material_free(mat->tile1);
    Material_free(mat->tile2);
    free(mat);
}
