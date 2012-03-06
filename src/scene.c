
#include <stdio.h>
#include <stdlib.h>

#include "ray.h"

Scene* Scene_new() {
    Scene* s = (Scene*) malloc(sizeof(Scene));
    s->objects = List_new();
    return s;
}

void Scene_add_object(Scene* scene, Object* obj) {
    List_append(scene->objects, (void*) obj);
}

void Scene_free(Scene* s) {
    //TODO
    printf("ERROR: Scene_free not yet implemented\n");
    exit(-1);
}
