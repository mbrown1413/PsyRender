
#include <stdio.h>
#include <stdlib.h>

#include "psyrender.h"

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

    ListNode* node = s->objects->head;
    while (node) {
        obj = (Object*) node->data;
        Object_free(obj);
        node = node->next;
    }

    List_free(s->objects);

    free(s);
}
