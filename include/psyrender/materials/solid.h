
#ifndef _PSY_MATERIAL_SOLID_H
#define _PSY_MATERIAL_SOLID_H

typedef struct {
    MATERIAL_HEADER
    Color ambient;
    Color diffuse;
    Color reflect;
    Color refract;
} Material_Solid;

Material* Material_Solid_new(
    unsigned char ambient_r, unsigned char ambient_g, unsigned char ambient_b,
    unsigned char diffuse_r, unsigned char diffuse_g, unsigned char diffuse_b,
    unsigned char reflect_r, unsigned char reflect_g, unsigned char reflect_b,
    unsigned char refract_r, unsigned char refract_g, unsigned char refract_b
);

Color Material_Solid_direction_scatter(const Material* mat,
                                       const SurfacePoint* sp,
                                       const Photon* in,
                                       const Ray* out);
PhotonList* Material_Solid_special_scatter(const Material* mat,
                                           const SurfacePoint* sp,
                                           const Photon* in);
void Material_Solid_free(Material* mat);

static const struct material_func_table material_solid_func_table = {
    Material_Solid_direction_scatter,
    Material_Solid_special_scatter,
    Material_Solid_free
};

#endif
