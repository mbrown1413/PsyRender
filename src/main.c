
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include "psyrender.h"

int main() {
    Canvas* canvas;
    Camera* camera;
    Renderer* renderer;
    Scene* scene = Scene_new();

    Material_Solid* mat_solid;
    Shape* shape;
    Object* sphere1;
    Object* sphere2;
    Object* sphere3;
    Object* plane;

    Light* light = Light_new(
        (Point) {1e100, 0, 1e100},
        (Color) {255, 255, 255}
    );
    Scene_add_light(scene, light);

    shape = Shape_Sphere_new(1);
    mat_solid = (Material_Solid*) Material_Solid_new(
        255 * 0.1,         0,         0,
        255 * 0.4,         0,         0,
        255 * 0.9, 255 * 0.9, 255 * 0.9,
                0,         0,         0
    );
    sphere1 = Object_new(shape, (Material*) mat_solid, NULL);
    Transform_translate(sphere1->trans, 2, 5, -1);
    Scene_add_object(scene, sphere1);

    shape = Shape_Sphere_new(1);
    mat_solid = (Material_Solid*) Material_Solid_new(
                0,         0, 255 * 0.1,
                0,         0, 255 * 0.4,
        255 * 0.9, 255 * 0.9, 255 * 0.9,
                0,         0,         0
    );
    sphere2 = Object_new(shape, (Material*) mat_solid, NULL);
    Transform_translate(sphere2->trans, -2, 7, -1);
    Scene_add_object(scene, sphere2);

    shape = Shape_Sphere_new(3);
    mat_solid = (Material_Solid*) Material_Solid_new(
                0, 255 * 0.1,         0,
                0, 255 * 0.4,         0,
        255 * 0.9, 255 * 0.9, 255 * 0.9,
                0,         0,         0
    );
    sphere3 = Object_new(shape, (Material*) mat_solid, NULL);
    Transform_translate(sphere3->trans, 0, 10, 1);
    Scene_add_object(scene, sphere3);

    shape = Shape_Plane_new(-2);
    Material* checker = Material_CheckerSolid_new(2,
        255*0.0, 255*0.0, 255*0.0,
        255*0.1, 255*0.1, 255*0.1,
        255*0.2, 255*0.2, 255*0.2,
              0,       0,       0,
        127*0.1, 127*0.1, 127*0.1,
        255*0.5, 255*0.5, 255*0.5,
        255*0.2, 255*0.2, 255*0.2,
              0,       0,       0
    );
    plane = Object_new(shape, (Material*) checker, NULL);
    Scene_add_object(scene, (Object*) plane);

    camera = (Camera*) Camera_Basic_new(
        (Point) {0, 0, 0}
    );

    canvas = Canvas_Png_new("output.png", 1600, 1600);

    renderer = Renderer_RayTraceSimple_new(20);

    Renderer_render(renderer, scene, camera, (Canvas*) canvas);

    Camera_free(camera);
    Scene_free(scene);
    Canvas_free(canvas);

}
