
#ifndef _RAY_MATERIAL_BASIC_H
#define _RAY_MATERIAL_BASIC_H

typedef struct {
    MATERIAL_HEADER
    Color color;
    double reflectivity;
} Material_Basic;

Material_Basic* Material_Basic_new();
Color Material_Basic_ray_hit(const Material* mat, Ray* ray, const Ray* norm, unsigned int depth);

#endif
