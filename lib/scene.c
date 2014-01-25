
#include <stdio.h>
#include <stdlib.h>

#include "psyrender.h"

Scene* Scene_new() {
    Scene* s = (Scene*) malloc(sizeof(Scene));
    s->objects = ObjectList_new();
    s->lights = LightList_new();
    return s;
}

void Scene_add_object(Scene* scene, Object* obj) {
    ObjectList_append(scene->objects, obj);
}

void Scene_add_light(Scene* scene, Light* light) {
    LightList_append(scene->lights, light);
}

bool Scene_ray_intersect(const Scene* scene, const Ray* r, SurfacePoint* sp_out) {
    SurfacePoint sp, closest_sp;
    double dist_sq, closest_dist_sq = INFINITY;
    bool found_intersection = false;

    for(int i=0; i<scene->objects->len; i++) {
        Object* obj = ObjectList_GET(scene->objects, i);

        if(Object_ray_intersect(obj, r, &sp)) {

            dist_sq = Vector_dist_squared(&sp.point, &r->o);

            //TODO: Remove this when ray.min_t is implemented
            if(dist_sq < 10*EPSILON) {
                continue;
            }

            if(dist_sq < closest_dist_sq) {
                found_intersection = true;
                closest_dist_sq = dist_sq;
                closest_sp = sp;
                closest_sp.obj = obj;
            }

        }

    }

    if(found_intersection) {
        if(sp_out != NULL) {
            *sp_out = closest_sp;
        }
        return true;
    } else {
        return false;
    }
}

void Scene_free(Scene* scene) {
    for(int i=0; i<scene->objects->len; i++) {
        Object_free(ObjectList_GET(scene->objects, i));
    }
    for(int i=0; i<scene->lights->len; i++) {
        Light_free(LightList_GET(scene->objects, i));
    }
    ObjectList_free(scene->objects);
    LightList_free(scene->lights);

    free(scene);
}
