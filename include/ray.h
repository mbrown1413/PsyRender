
#ifndef _RAY_H
#define _RAY_H

#include <math.h>

#ifdef M_PI
    #define PI M_PI
#else
    #define PI 3.141592653589793238462643383279
#endif

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

// These typedefs resolve any circular dependancies between the types.
struct Object_struct;
typedef struct Object_struct Object;

struct Material_struct;
typedef struct Material_struct Material;

struct Camera_struct;
typedef struct Camera_struct Camera;

struct Canvas_struct;
typedef struct Canvas_struct Canvas;

#include "vector_math.h"
#include "linked_list.h"

#include "scene.h"
#include "material.h"
#include "object.h"
#include "camera.h"
#include "canvas.h"
#include "render.h"

#endif
