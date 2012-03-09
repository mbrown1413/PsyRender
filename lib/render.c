
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ray.h"

bool render(const Scene* scene, const Camera* camera, Canvas* canvas) {
    if (!Canvas_init(canvas, camera)) {
        fprintf(stderr, canvas->error_str);
        fprintf(stderr, "\n");
        return false;
    }
    Camera_render(scene, camera, canvas);
    Canvas_finish(canvas);
    return true;
}

Color trace_ray(const Scene* scene, const Ray* r, unsigned int depth) {
    Point intersect;
    Vector norm;
    Object* obj;

    obj = ray_intersect(scene, r, &intersect);

    if (obj) {
        Object_normal(obj, &intersect, &norm);

        Material* mat = obj->mat;
        Color mat_color = Material_ray_hit(scene, mat, r, &intersect, &norm, depth+1);

        if (mat->reflectivity) {
            Ray reflected;
            ray_reflect(&reflected, r, &intersect, &norm);
            Color reflected_color = trace_ray(scene, &reflected, depth);
            return (Color) {
                (1-mat->reflectivity)*mat_color.r + mat->reflectivity*reflected_color.r,
                (1-mat->reflectivity)*mat_color.g + mat->reflectivity*reflected_color.g,
                (1-mat->reflectivity)*mat_color.b + mat->reflectivity*reflected_color.b
            };
        }

        return mat_color;

    } else {
        return (Color) {0, 0, 0};
    }
}

Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect) {
    Point obj_intersect, closest_intersect;
    double dist, closest_dist = INFINITY;
    Object* obj;
    Object* closest_obj=NULL;

    List_start_iteration(scene->objects);
    while ((obj = (Object*) List_next(scene->objects))) {

        if (Object_ray_intersect(obj, r, &obj_intersect)) {
            dist = DIST_SQ(obj_intersect.x, obj_intersect.y, obj_intersect.z, r->ox, r->oy, r->oz);
            if (dist < closest_dist) {
                closest_dist = dist;
                closest_intersect = obj_intersect;
                closest_obj = obj;
            }
        }
    }
    *intersect = closest_intersect;
    return closest_obj;
}
