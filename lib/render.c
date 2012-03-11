
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

    obj = ray_intersect(scene, r, &intersect);

    if (!obj) {
        return (Color) {0, 0, 0};
    }

    Object_normal(obj, &intersect, &norm);
    Material* mat = obj->mat;
    mat_color = Material_ray_hit(scene, mat, r, &intersect, &norm, depth+1);
    vec_normalize(&norm);

    // Ambient
    result.r += mat_color.r * mat->ambient;
    result.g += mat_color.g * mat->ambient;
    result.b += mat_color.b * mat->ambient;

    // Diffuse
    Vector light_direction = {1, 0, 1};
    vec_normalize(&light_direction);
    result.r += MAX(0,mat_color.r*mat->diffuse * DOT(light_direction.x, light_direction.y, light_direction.z, norm.x, norm.y, norm.z));
    result.g += MAX(0,mat_color.g*mat->diffuse * DOT(light_direction.x, light_direction.y, light_direction.z, norm.x, norm.y, norm.z));
    result.b += MAX(0,mat_color.b*mat->diffuse * DOT(light_direction.x, light_direction.y, light_direction.z, norm.x, norm.y, norm.z));

    // Reflective
    if (mat->reflective) {
        Ray reflected;
        ray_reflect(&reflected, r, &intersect, &norm);
        tmp_color = trace_ray(scene, &reflected, depth);
        result.r = MIN(255, result.r + mat->reflective * tmp_color.r);
        result.g = MIN(255, result.g + mat->reflective * tmp_color.g);
        result.b = MIN(255, result.b + mat->reflective * tmp_color.b);
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

            dist = DIST_SQ(obj_intersect.x, obj_intersect.y, obj_intersect.z, r->ox, r->oy, r->oz);
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
