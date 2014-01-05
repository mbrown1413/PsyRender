
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

bool Scene_ray_intersect(const Scene* scene, const Ray* r, SurfacePoint* sp_out) {
    SurfacePoint sp, closest_sp;
    double dist_sq, closest_dist_sq = INFINITY;
    bool found_intersection = false;

    ListNode* node = scene->objects->head;
    while(node) {
        Object* obj = (Object*) node->data;

        if(Object_ray_intersect(obj, r, &sp)) {

            dist_sq = Vector_dist_squared(&sp.point, &r->o);

            //TODO: Remove this when ray.min_t is implemented
            if(dist_sq < 10*EPSILON) {
                node = node->next;
                continue;
            }

            if(dist_sq < closest_dist_sq) {
                found_intersection = true;
                closest_dist_sq = dist_sq;
                closest_sp = sp;
                closest_sp.obj = obj;
            }

        }

        node = node->next;
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

void Scene_free(Scene* s) {
    Object* obj;

    ListNode* node = s->objects->head;
    while(node) {
        obj = (Object*) node->data;
        Object_free(obj);
        node = node->next;
    }

    List_free(s->objects);

    free(s);
}
