
#include <stdio.h>
#include <stdlib.h>

#include "psyrender.h"

int main() {
    Material_Solid* mat_solid;

    Object* sphere;
    Object* plane;

    Canvas* canvas;
    Camera* camera;

    Scene* scene = Scene_new();

    Renderer* renderer;

    sphere = Object_Sphere_new(2, 5, -1, 1);
    mat_solid = (Material_Solid*) sphere->mat;
    mat_solid->transmit.ambient = (Color) {0.1 * 255, 0, 0};
    mat_solid->transmit.diffuse = (Color) {0.4 * 255, 0, 0};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    Scene_add_object(scene, (Object*) sphere);

    sphere = Object_Sphere_new(-2, 7, -1, 1);
    mat_solid = (Material_Solid*) sphere->mat;
    mat_solid->transmit.ambient = (Color) {0, 0, 0.1 * 255};
    mat_solid->transmit.diffuse = (Color) {0, 0, 0.4 * 255};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    Scene_add_object(scene, (Object*) sphere);

    sphere = Object_Sphere_new(0, 10, 1, 3);
    mat_solid = (Material_Solid*) sphere->mat;
    mat_solid->transmit.ambient = (Color) {0, 0.1 * 255, 0};
    mat_solid->transmit.diffuse = (Color) {0, 0.4 * 255, 0};
    mat_solid->transmit.reflect = (Color) {255 * 0.9, 255 * 0.9, 255 * 0.9};
    mat_solid->transmit.refract = (Color) {0, 0, 0};
    Scene_add_object(scene, (Object*) sphere);

    plane = Object_Plane_new(-2);
    Object_set_material((Object*) plane, Material_Checker_new(2));
    ((Material_Checker*)plane->mat)->tile1_transmit.ambient = (Color) {255*0.0, 255*0.0, 255*0.0};
    ((Material_Checker*)plane->mat)->tile1_transmit.diffuse = (Color) {255*0.1, 255*0.1, 255*0.1};
    ((Material_Checker*)plane->mat)->tile1_transmit.reflect = (Color) {255*0.2, 255*0.2, 255*0.2};
    ((Material_Checker*)plane->mat)->tile2_transmit.ambient = (Color) {127*0.1, 127*0.1, 127*0.1};
    ((Material_Checker*)plane->mat)->tile2_transmit.diffuse = (Color) {127, 127, 127};
    ((Material_Checker*)plane->mat)->tile2_transmit.reflect = (Color) {255*0.2, 255*0.2, 255*0.2};
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
