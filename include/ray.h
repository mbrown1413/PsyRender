
#ifndef _RAY_H
#define _RAY_H

#include <math.h>

#ifdef M_PI
    #define PI M_PI
#else
    #define PI 3.141592653589793238462643383279
#endif

// Guess at the maximum floating point error.  Used for comparing floating
// point numbers.
#define EPSILON ( 1.0e-5 )

// Index of refraction for the medium that contains no objects.
#define ETHER_INDEX_OF_REFRACTION 1.000277

#define MIN(a, b) ( (a)<(b) ? (a) : (b) )
#define MAX(a, b) ( (a)>(b) ? (a) : (b) )

typedef struct {
    double x, y, z;
} Vector;

typedef Vector Point;

typedef struct {
    Point o;  // Origin
    Vector d;  // Direction
} Ray;

// These typedefs resolve any circular dependancies between types.
struct Object_struct;
struct Material_struct;
struct Camera_struct;
struct Canvas_struct;
typedef struct Object_struct Object;
typedef struct Material_struct Material;
typedef struct Camera_struct Camera;
typedef struct Canvas_struct Canvas;

#include "vector.h"
#include "linked_list.h"
#include "color.h"

#include "scene.h"
#include "material.h"
#include "object.h"
#include "camera.h"
#include "canvas.h"
#include "render.h"

#endif
