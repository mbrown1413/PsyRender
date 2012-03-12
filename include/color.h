
#ifndef _RAY_COLOR_H
#define _RAY_COLOR_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

void Color_add(Color* result, const Color* a, const Color* b);
void Color_subtract(Color* result, const Color* a, const Color* b);
void Color_scalar_mult(Color* result, const Color* c, double value);

#endif
