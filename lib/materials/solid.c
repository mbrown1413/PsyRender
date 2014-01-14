
#include <stdlib.h>

#include "psyrender.h"

Material* Material_Solid_new(
    unsigned char ambient_r, unsigned char ambient_g, unsigned char ambient_b,
    unsigned char diffuse_r, unsigned char diffuse_g, unsigned char diffuse_b,
    unsigned char reflect_r, unsigned char reflect_g, unsigned char reflect_b,
    unsigned char refract_r, unsigned char refract_g, unsigned char refract_b
) {
    Material_Solid* m = (Material_Solid*) malloc(sizeof(Material_Solid));
    m->func = material_solid_func_table;
    m->ambient = (Color) {ambient_r, ambient_g, ambient_b};
    m->diffuse = (Color) {diffuse_r, diffuse_g, diffuse_b};
    m->reflect = (Color) {reflect_r, reflect_g, reflect_b};
    m->refract = (Color) {refract_r, refract_g, refract_b};
    return (Material*) m;
}

Color Material_Solid_direction_scatter(const Material* _mat,
                                       const SurfacePoint* sp,
                                       const Photon* in,
                                       const Ray* out) {
    const Material_Solid* mat = (const Material_Solid*) _mat;
    Color tmp_color, result = (Color) {0, 0, 0};

    // Diffuse
    double angle_factor = MAX(0, -Vector_dot(&in->ray.d, &sp->norm));
    if(angle_factor > 0) {
        Color_scalar_mult(&tmp_color, &mat->diffuse, angle_factor);
        Color_add(&result, &result, &tmp_color);
    }
    Color_mult(&result, &result, &in->color);

    // Ambient
    Color_add(&result, &result, &mat->ambient);

    return result;
}

PhotonList* Material_Solid_special_scatter(const Material* _mat,
                                           const SurfacePoint* sp,
                                           const Photon* in) {
    const Material_Solid* mat = (const Material_Solid*) _mat;
    PhotonList* photons = PhotonList_new();

    // Reflective
    Photon* p = (Photon*) malloc(sizeof(Photon));
    Ray_reflect(&p->ray, &in->ray, &sp->point, &sp->norm);
    Color_mult(&p->color, &in->color, &mat->reflect);
    PhotonList_append(photons, p);

    // Refractive
    //TODO

    return photons;
}

void Material_Solid_free(Material* mat) {
    free(mat);
}
