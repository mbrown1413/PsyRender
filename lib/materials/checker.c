
#include <math.h>

#include "psyrender.h"

Material* Material_Checker_new(unsigned int scale) {
    Material_Checker* m = (Material_Checker*) malloc(sizeof(Material_Checker));
    m->func = material_checker_func_table;
    m->scale = scale;
    m->tile1_transmit = (struct material_transmit) {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    m->tile2_transmit = (struct material_transmit) {
        {0, 0, 0},
        {255 ,255, 255},
        {0, 0, 0},
        {0, 0, 0}
    };
    return (Material*) m;
}

struct material_transmit Material_Checker_get_transmit(const Material* _m, const Object* object, const Point* intersect) {
    Material_Checker* m = (Material_Checker*) _m;

    if (( ((int) round(intersect->x)) / m->scale + \
          ((int) round(intersect->y)) / m->scale + \
          ((int) round(intersect->z)) / m->scale) % 2)
    {
        return m->tile1_transmit;
    } else {
        return m->tile2_transmit;
    }
}
