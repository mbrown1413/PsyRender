/**
 * .. todo:: Material Documentation
 */

#ifndef _PSY_MATERIAL_H
#define _PSY_MATERIAL_H

#define MATERIAL_HEADER \
    struct material_func_table func; \

struct material_transmit {
    Color diffuse;
    Color ambient;
    Color reflect;
    Color refract;
};

struct material_func_table {
    struct material_transmit (*get_transmit)(const Material* mat, const Object* object, const Point* intersect);
};

struct Material_struct {
    MATERIAL_HEADER
};

Material* Material_new_default();

#define Material_get_transmit(...) INTERFACE_CALL_FUNC(Material, get_transmit, __VA_ARGS__)
#define Material_free(m) free(m)

#include "materials/solid.h"
#include "materials/checker.h"

#endif
