
#include <stdio.h>
#include <stdlib.h>

#include "ray.h"

int main() {
    Material_Basic* mat_basic;
    Sphere* sphere;

    Scene* scene = Scene_new();

    sphere = Sphere_new(2, 5, -1, 1);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {0, 0, 0};
    mat_basic->reflectivity = 1.0;
    Scene_add_object(scene, (Object*) sphere);

    sphere = Sphere_new(-2, 7, -1, 1);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {0, 0, 0};
    mat_basic->reflectivity = 1.0;
    Scene_add_object(scene, (Object*) sphere);

    sphere = Sphere_new(0, 10, 1, 3);
    mat_basic = (Material_Basic*) sphere->mat;
    mat_basic->color = (Color) {0, 0, 0};
    mat_basic->reflectivity = 1.0;
    Scene_add_object(scene, (Object*) sphere);

    Plane* plane = Plane_new(-2);
    /*
    mat_basic = (Material_Basic*) plane->mat_basic;
    mat_basic->color = (Color) {255, 255, 255};
    */
    Object_set_material((Object*) plane, Material_Checker_new(2));
    Scene_add_object(scene, (Object*) plane);

    Camera* camera = Camera_new();
    camera->width = 1600;
    camera->height = 1600;

    render(camera, scene, "output.png");

    //Scene_free(scene);

}
