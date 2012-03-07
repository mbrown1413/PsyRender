
#ifndef _RAY_H
#define _RAY_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

typedef struct {
    double ox, oy, oz;  // Origin
    double dx, dy, dz;  // Direction
} Ray;

typedef struct {
    double x, y, z;
} Point;

#define DOT(x1,y1,z1, x2,y2,z2) ( (x1)*(x2) + (y1)*(y2) + (z1)*(z2) )
#define DIST_SQ(x1,y1,z1, x2,y2,z2) ( ((x1)-(x2))*((x1)-(x2)) + ((y1)-(y2))*((y1)-(y2)) + ((z1)-(z2))*((z1)-(z2)) )

struct Object_struct;
typedef struct Object_struct Object;

struct Material_struct;
typedef struct Material_struct Material;

#include "linked_list.h"
#include "scene.h"
#include "material.h"
#include "object.h"
#include "camera.h"
#include "render.h"

#endif
