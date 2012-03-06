
#include <stdio.h>
#include <stdlib.h>

#include "ray.h"

int main() {

    Scene* scene = Scene_new();
    Scene_add_object(scene, (Object*) Sphere_new(0, 5, 0, 1));

    Camera* camera = Camera_new();
    camera->width = 900;
    camera->height = 900;

    render(camera, scene, "output.png");

    //Scene_free(scene);

}
