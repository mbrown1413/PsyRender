
#ifndef _PSY_H
#define _PSY_H

#include <math.h>
#include <stdbool.h>

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
#define CLAMP(min, x, max) MIN(max, MAX(min, x))

// Used to define interface functions
#define INTERFACE_CALL_FUNC(type, to_call, instance, ...) (instance)->func.to_call((type*) instance, __VA_ARGS__)
#define INTERFACE_CALL_FUNC_NO_ARGS(type, to_call, instance) (instance)->func.to_call((type*) instance)


// These typedefs resolve any circular dependancies between types.
typedef struct Renderer_struct Renderer;
typedef struct Shape_struct Shape;
typedef struct Object_struct Object;
typedef struct Material_struct Material;
typedef struct Camera_struct Camera;
typedef struct Canvas_struct Canvas;
typedef struct Scene_struct Scene;
typedef struct Volume_struct Volume;

#include "psyrender/data_structs/vector.h"
#include "psyrender/data_structs/point.h"
#include "psyrender/data_structs/ray.h"
#include "psyrender/data_structs/ptrlist.h"
#include "psyrender/data_structs/color.h"
#include "psyrender/data_structs/matrix4x4.h"
#include "psyrender/data_structs/transform.h"
#include "psyrender/data_structs/photon.h"

#include "psyrender/surface_point.h"
#include "psyrender/material.h"
#include "psyrender/volume.h"
#include "psyrender/shape.h"
#include "psyrender/object.h"
#include "psyrender/camera.h"
#include "psyrender/canvas.h"
#include "psyrender/renderer.h"
#include "psyrender/scene.h"

#endif
