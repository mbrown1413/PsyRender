
#ifndef _RAY_H
#define _RAY_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

typedef struct {
    double x, y, z;
} Point;

typedef struct {
    double x, y, z;
} Vector;

typedef struct {
    double ox, oy, oz;  // Origin
    double dx, dy, dz;  // Direction
} Ray;

struct Object_struct;
typedef struct Object_struct Object;

struct Material_struct;
typedef struct Material_struct Material;

#include "vector_math.h"
#include "linked_list.h"

#include "scene.h"
#include "material.h"
#include "object.h"
#include "camera.h"
#include "render.h"

#endif
