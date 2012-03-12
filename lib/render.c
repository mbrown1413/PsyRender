
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ray.h"

bool render(const Scene* scene, const Camera* camera, Canvas* canvas) {
    if (!Canvas_init(canvas, camera)) {
        fprintf(stderr, "Error initializing canvas: ");
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
    Color result = {0, 0, 0};
    Color mat_color;
    Color tmp_color;
    Ray tmp_ray;

    obj = ray_intersect(scene, r, &intersect);

    if (!obj) {
        return (Color) {0, 0, 0};
    }

    Object_normal(obj, &intersect, &norm);
    Material* mat = obj->mat;
    mat_color = Material_ray_hit(scene, mat, r, &intersect, &norm, depth+1);
    Vector_normalize(&norm);

    // Ambient
    Color_scalar_mult(&result, &mat_color, mat->ambient);

    // Diffuse
    Vector light_direction = {1, 0, 1}; // One hardcoded light for now :/
    Vector_normalize(&light_direction);

    tmp_color = mat_color;
    double angle_factor = MAX(0, Vector_dot(&light_direction, &norm));
    Color_scalar_mult(&tmp_color, &tmp_color, mat->diffuse * angle_factor);
    Color_add(&result, &result, &tmp_color);

    // Reflective
    if (mat->reflective) {
        ray_reflect(&tmp_ray, r, &intersect, &norm);
        tmp_color = trace_ray(scene, &tmp_ray, depth);
        Color_scalar_mult(&tmp_color, &tmp_color, mat->reflective);
        Color_add(&result, &result, &tmp_color);
    }

    return result;
}

Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect) {
    Point obj_intersect, closest_intersect={INFINITY, INFINITY, INFINITY};
    double dist, closest_dist = INFINITY;
    Object* obj;
    Object* closest_obj = NULL;

    List_start_iteration(scene->objects);
    while ((obj = (Object*) List_next(scene->objects))) {

        if (Object_ray_intersect(obj, r, &obj_intersect)) {

            dist = Vector_dist_squared(&obj_intersect, &r->o);
            if (dist < closest_dist) {
                closest_dist = dist;
                closest_intersect = obj_intersect;
                closest_obj = obj;
            }

        }
    }
    if (closest_obj != NULL) {
        *intersect = closest_intersect;
    }
    return closest_obj;
}
