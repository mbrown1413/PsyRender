
#ifndef _RAY_MATERIAL_SOLID_H
#define _RAY_MATERIAL_SOLID_H

typedef struct {
    MATERIAL_HEADER
    Color color;
} Material_Solid;

Material* Material_Solid_new();
Color Material_Solid_ray_hit(
        const Scene* scene,
        const Material* mat,
        const Ray* ray,
        Point* intersect,
        Vector* norm,
        unsigned int depth);

#endif
