/**
 * .. todo:: Document Color
 */

#ifndef _PSY_COLOR_H
#define _PSY_COLOR_H

#include <stdbool.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

void Color_add(Color* result, const Color* a, const Color* b);
void Color_subtract(Color* result, const Color* a, const Color* b);
void Color_scalar_mult(Color* result, const Color* c, double value);
void Color_mult(Color* result, const Color* a, const Color* b);
bool Color_is_black(const Color* c);

#endif
