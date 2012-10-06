
#include "psyrender.h"

void Color_add(Color* result, const Color* c1, const Color* c2) {
    result->r = MIN(255, c1->r + c2->r);
    result->g = MIN(255, c1->g + c2->g);
    result->b = MIN(255, c1->b + c2->b);
}

void Color_subtract(Color* result, const Color* c1, const Color* c2) {
    result->r = MAX(0, c1->r - c2->r);
    result->g = MAX(0, c1->g - c2->g);
    result->b = MAX(0, c1->b - c2->b);
}

void Color_scalar_mult(Color* result, const Color* c, double value) {
    result->r = MIN(255, c->r * value);
    result->g = MIN(255, c->g * value);
    result->b = MIN(255, c->b * value);
}
