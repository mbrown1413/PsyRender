
#ifndef _PSY_MATERIAL_SOLID_H
#define _PSY_MATERIAL_SOLID_H

typedef struct {
    MATERIAL_HEADER
    struct material_transmit transmit;
} Material_Solid;

Material* Material_Solid_new();
struct material_transmit Material_Solid_get_transmit(const Material* mat, const Object* object, const Point* intersect);

static const struct material_func_table material_solid_func_table = {
    *Material_Solid_get_transmit
};

#endif
