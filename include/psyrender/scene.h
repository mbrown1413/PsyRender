/**
 * .. todo:: Scene Documentation
 */

#ifndef _PSY_SCENE_H
#define _PSY_SCENE_H

typedef struct {
    List* objects;
    //List* lights;
} Scene;

Scene* Scene_new();
void Scene_add_object(Scene* scene, Object* obj);
void Scene_free(Scene* s);

#endif
