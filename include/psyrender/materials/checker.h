
#ifndef _PSY_MATERIAL_CHECKER_H
#define _PSY_MATERIAL_CHECKER_H

typedef struct {
    MATERIAL_HEADER
    unsigned int scale;
    Material* tile1;
    Material* tile2;
} Material_Checker;

Material* Material_Checker_new(unsigned int scale, Material* tile1, Material* tile2);
Color Material_Checker_direction_scatter(const Material* mat,
                                         const SurfacePoint* sp,
                                         const Photon* in,
                                         const Ray* out);
PhotonArray* Material_Checker_special_scatter(const Material* mat,
                                             const SurfacePoint* sp,
                                             const Photon* in);
void Material_Checker_free(Material* mat);
void Material_Checker_free_with_tiles(Material* mat);

static const struct material_func_table material_checker_func_table = {
    Material_Checker_direction_scatter,
    Material_Checker_special_scatter,
    Material_Checker_free
};

/**
 * A shortcut for making a checker material where tile1 and tile2 are solid
 * materials.
 */
static inline Material* Material_CheckerSolid_new(unsigned int scale,
    unsigned char m1_ambient_r, unsigned char m1_ambient_g, unsigned char m1_ambient_b,
    unsigned char m1_diffuse_r, unsigned char m1_diffuse_g, unsigned char m1_diffuse_b,
    unsigned char m1_reflect_r, unsigned char m1_reflect_g, unsigned char m1_reflect_b,
    unsigned char m1_refract_r, unsigned char m1_refract_g, unsigned char m1_refract_b,
    unsigned char m2_ambient_r, unsigned char m2_ambient_g, unsigned char m2_ambient_b,
    unsigned char m2_diffuse_r, unsigned char m2_diffuse_g, unsigned char m2_diffuse_b,
    unsigned char m2_reflect_r, unsigned char m2_reflect_g, unsigned char m2_reflect_b,
    unsigned char m2_refract_r, unsigned char m2_refract_g, unsigned char m2_refract_b
) {
    Material* m1 = Material_Solid_new(
        m1_ambient_r, m1_ambient_g, m1_ambient_b,
        m1_diffuse_r, m1_diffuse_g, m1_diffuse_b,
        m1_reflect_r, m1_reflect_g, m1_reflect_b,
        m1_refract_r, m1_refract_g, m1_refract_b
    );
    Material* m2 = Material_Solid_new(
        m2_ambient_r, m2_ambient_g, m2_ambient_b,
        m2_diffuse_r, m2_diffuse_g, m2_diffuse_b,
        m2_reflect_r, m2_reflect_g, m2_reflect_b,
        m2_refract_r, m2_refract_g, m2_refract_b
    );
    Material* checker = Material_Checker_new(scale, m1, m2);
    ((Material_Checker*) checker)->func.free = Material_Checker_free_with_tiles;
    return checker;
}

#endif
