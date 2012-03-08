
#ifndef _RAY_MATERIAL_BASIC_H
#define _RAY_MATERIAL_BASIC_H

typedef struct {
    MATERIAL_HEADER
    Color color;
} Material_Basic;

Material* Material_Basic_new();
Color Material_Basic_ray_hit(const Scene* scene, const Material* mat, const Ray* ray, Ray* norm, unsigned int depth);

#endif
