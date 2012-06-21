
#include <stdio.h>
#include <stdlib.h>

#include "ray.h"

int main() {
    Material_Basic* mat_basic;

    Sphere* sphere;
    Plane* plane;

    Canvas* canvas;
    Camera* camera;

    Scene* scene = Scene_new();

    sphere = Sphere_new(2, 5, -1, 1);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {255, 0, 0};
    mat_basic->diffuse = 0.4;
    mat_basic->ambient = 0.1;
    mat_basic->reflective = 0.9;
    Scene_add_object(scene, (Object*) sphere);

    sphere = Sphere_new(-2, 7, -1, 1);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {0, 0, 255};
    mat_basic->diffuse = 0.4;
    mat_basic->ambient = 0.1;
    mat_basic->reflective = 0.9;
    Scene_add_object(scene, (Object*) sphere);

    sphere = Sphere_new(0, 10, 1, 3);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {0, 255, 0};
    mat_basic->diffuse = 0.4;
    mat_basic->ambient = 0.1;
    mat_basic->reflective = 0.9;
    Scene_add_object(scene, (Object*) sphere);

    plane = Plane_new(-2);
    Object_set_material((Object*) plane, Material_Checker_new(2));
    plane->mat->ambient = 0.0;
    plane->mat->diffuse = .5;
    plane->mat->reflective = 0.2;
    Scene_add_object(scene, (Object*) plane);

    camera = (Camera*) Camera_Basic_new(
        (Point) {0, 0, 0}
    );

    canvas = Canvas_Png_new("output.png", 1600, 1600);

    render(scene, camera, canvas);

    Camera_free(camera);
    Scene_free(scene);
    Canvas_free(canvas);

}
