
#ifndef _PSY_MATERIAL_CHECKER_H
#define _PSY_MATERIAL_CHECKER_H

typedef struct {
    MATERIAL_HEADER
    unsigned int scale;
    struct material_transmit tile1_transmit;
    struct material_transmit tile2_transmit;
} Material_Checker;

Material* Material_Checker_new(unsigned int scale);
struct material_transmit Material_Checker_get_transmit(const Material* mat, const Object* object, const Point* intersect);

static const struct material_func_table material_checker_func_table = {
    *Material_Checker_get_transmit
};

#endif
