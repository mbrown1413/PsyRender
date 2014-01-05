
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

    renderer = Renderer_RayTraceSimple_new(UINT_MAX);

    shape = Shape_Sphere_new(1);
    mat_solid = (Material_Solid*) Material_Solid_new();
    mat_solid->transmit.ambient = (Color) {0.1 * 255, 0, 0};
    mat_solid->transmit.diffuse = (Color) {0.4 * 255, 0, 0};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    sphere1 = Object_new(shape, (Material*) mat_solid, NULL);
    Transform_translate(sphere1->trans, 2, 5, -1);
    Scene_add_object(scene, sphere1);

    shape = Shape_Sphere_new(1);
    mat_solid = (Material_Solid*) Material_Solid_new();
    mat_solid->transmit.ambient = (Color) {0, 0, 0.1 * 255};
    mat_solid->transmit.diffuse = (Color) {0, 0, 0.4 * 255};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    sphere2 = Object_new(shape, (Material*) mat_solid, NULL);
    Transform_translate(sphere2->trans, -2, 7, -1);
    Scene_add_object(scene, sphere2);

    shape = Shape_Sphere_new(3);
    mat_solid = (Material_Solid*) Material_Solid_new();
    mat_solid->transmit.ambient = (Color) {0, 0.1 * 255, 0};
    mat_solid->transmit.diffuse = (Color) {0, 0.4 * 255, 0};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    sphere3 = Object_new(shape, (Material*) mat_solid, NULL);
    Transform_translate(sphere3->trans, 0, 10, 1);
    Scene_add_object(scene, sphere3);

    shape = Shape_Plane_new(-2);
    Material_Checker* checker = (Material_Checker*) Material_Checker_new(2);
    plane = Object_new(shape, (Material*) checker, NULL);
    checker->tile1_transmit.ambient = (Color) {255*0.0, 255*0.0, 255*0.0};
    checker->tile1_transmit.diffuse = (Color) {255*0.1, 255*0.1, 255*0.1};
    checker->tile1_transmit.reflect = (Color) {255*0.2, 255*0.2, 255*0.2};
    checker->tile2_transmit.ambient = (Color) {127*0.1, 127*0.1, 127*0.1};
    checker->tile2_transmit.diffuse = (Color) {127, 127, 127};
    checker->tile2_transmit.reflect = (Color) {255*0.2, 255*0.2, 255*0.2};
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
