/**
 * .. todo:: Scene Documentation
 */

#ifndef _PSY_SCENE_H
#define _PSY_SCENE_H

struct Scene_struct {
    ObjectList* objects;
    LightList* lights;
};

/**
 * Returns a new blank scene.
 */
Scene* Scene_new();

/**
 * Adds an object to the scene.
 */
void Scene_add_object(Scene* scene, Object* obj);

/**
 * Adds a light to the scene.
 */
void Scene_add_light(Scene* scene, Light* light);

/**
 * Calculate the closest intersection of the ray in the scene.
 *
 * Surface properties at the intersection point are stored in ``sp_out`` if it
 * is not NULL.
 */
bool Scene_ray_intersect(const Scene* scene, const Ray* r, SurfacePoint* sp_out);

/**
 * TODO: Function documentation
 */
void Scene_free(Scene* s);

#endif
