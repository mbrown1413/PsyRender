
#include <stdlib.h>

#include "psyrender.h"

Material* Material_Solid_new() {
    Material_Solid* m = (Material_Solid*) malloc(sizeof(Material_Solid));
    m->func = material_solid_func_table;
    m->transmit = (struct material_transmit) {
        {255, 255, 255},
        {255, 255, 255},
        {0, 0, 0},
        {0, 0, 0}
    };
    return (Material*) m;
}

struct material_transmit Material_Solid_get_transmit(const Material* mat, const Object* object, const Point* intersect) {
    Material_Solid* m = (Material_Solid*) mat;
    return m->transmit;
}
