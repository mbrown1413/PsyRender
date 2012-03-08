
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
    Object* obj;

    List_start_iteration(s->objects);
    while ((obj = (Object*) List_next(s->objects))) {
        Object_free(obj);
    }
    List_free(s->objects);

    free(s);
}
