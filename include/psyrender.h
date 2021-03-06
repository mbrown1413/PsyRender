
#ifndef _PSY_H
#define _PSY_H

#include <math.h>

#ifdef M_PI
    #define PI M_PI
#else
    #define PI 3.141592653589793238462643383279
#endif

// Guess at the maximum floating point rounding error. Used for comparing
// floating point numbers.
#define EPSILON ( 1.0e-5 )

// Index of refraction for the medium that contains no objects.
#define ETHER_INDEX_OF_REFRACTION 1.000277

#define MIN(a, b) ( (a)<(b) ? (a) : (b) )
#define MAX(a, b) ( (a)>(b) ? (a) : (b) )

// Used to define interface functions
#define INTERFACE_CALL_FUNC(type, to_call, instance, ...) (instance)->func.to_call((type*) instance, __VA_ARGS__)
#define INTERFACE_CALL_FUNC_NO_ARGS(type, to_call, instance) (instance)->func.to_call((type*) instance)

// These typedefs resolve any circular dependancies between types.
struct Renderer_struct;
struct Object_struct;
struct Material_struct;
struct Camera_struct;
struct Canvas_struct;
typedef struct Renderer_struct Renderer;
typedef struct Object_struct Object;
typedef struct Material_struct Material;
typedef struct Camera_struct Camera;
typedef struct Canvas_struct Canvas;

#include "psyrender/data_structs/vector.h"
#include "psyrender/data_structs/ray.h"
#include "psyrender/data_structs/linked_list.h"
#include "psyrender/data_structs/color.h"

#include "psyrender/scene.h"
#include "psyrender/material.h"
#include "psyrender/object.h"
#include "psyrender/camera.h"
#include "psyrender/canvas.h"
#include "psyrender/renderer.h"

#endif
