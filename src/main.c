
#include <stdio.h>
#include <stdlib.h>

#include "ray.h"

int main() {
    Material_Basic* mat;

    Scene* scene = Scene_new();

    Sphere* sphere = Sphere_new(0, 5, -2, 1);
    mat = (Material_Basic*) sphere->mat;
    mat->color = (Color) {127, 127, 127};
    Scene_add_object(scene, (Object*) sphere);

    Plane* plane = Plane_new(-2);
    mat = (Material_Basic*) sphere->mat;
    mat->color = (Color) {0, 255, 0};
    Scene_add_object(scene, (Object*) plane);

    Camera* camera = Camera_new();
    camera->width = 900;
    camera->height = 900;

    render(camera, scene, "output.png");

    //Scene_free(scene);

}
