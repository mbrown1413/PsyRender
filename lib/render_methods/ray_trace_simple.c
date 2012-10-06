
#include "psyrender.h"

Color trace_ray(const Scene* scene, const Ray* _r, unsigned int depth, double n1);
Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect);

RenderMeth* RenderMeth_RayTraceSimple_new() {
    RenderMeth_RayTraceSimple* render_meth = (RenderMeth_RayTraceSimple*) malloc(sizeof(RenderMeth_RayTraceSimple));
    render_meth->func.render = RenderMeth_RayTraceSimple_render;
    return (RenderMeth*) render_meth;
}

bool RenderMeth_RayTraceSimple_render(RenderMeth* meth, Scene* scene, Camera* cam, Canvas* canvas) {
    Color* row;
    Ray ray;

    Canvas_start(canvas);

    for (int y=canvas->height-1; y>=0; y--) {
        row = Canvas_get_next_row(canvas);
        for (int x=0; x<canvas->width; x++) {
            Camera_map(cam, ((double)x)/canvas->width, ((double)y)/canvas->height, &ray);
            row[x] = trace_ray(scene, &ray, 0, ETHER_INDEX_OF_REFRACTION);
        }
        Canvas_write_row(canvas, row);
    }

    Canvas_finish(canvas);
    return true;
}

Color trace_ray(const Scene* scene, const Ray* _r, unsigned int depth, double n1) {
    Point intersect;
    Vector norm;
    Object* obj;
    Color result = {0, 0, 0};
    Color mat_color;
    Color tmp_color;
    Ray r, tmp_ray;

    Vector_assign(&r.o, &_r->o);
    Vector_assign(&r.d, &_r->d);
    Vector_normalize(&r.d);

    obj = ray_intersect(scene, &r, &intersect);

    if (!obj) {
        return (Color) {0, 0, 0};
    }

    Object_normal(obj, &intersect, &norm);
    Material* mat = obj->mat;
    mat_color = Material_ray_hit(scene, mat, &r, &intersect, &norm, depth+1);
    Vector_normalize(&norm);

    // Ambient
    Color_scalar_mult(&result, &mat_color, mat->ambient);

    // Diffuse
    Vector light_direction = {1, 0, 1}; // TODO: One hardcoded light for now
    Vector_normalize(&light_direction);

    tmp_color = mat_color;
    double angle_factor = MAX(0, Vector_dot(&light_direction, &norm));
    Color_scalar_mult(&tmp_color, &tmp_color, mat->diffuse * angle_factor);
    Color_add(&result, &result, &tmp_color);

    if (Object_inside(obj, &r.o)) {
        Vector_scalar_mult(&norm, &norm, -1);
    }

    // Reflective
    if (mat->reflective) {
        ray_reflect(&tmp_ray, &r, &intersect, &norm);
        tmp_color = trace_ray(scene, &tmp_ray, depth+1, n1);
        Color_scalar_mult(&tmp_color, &tmp_color, mat->reflective);
        Color_add(&result, &result, &tmp_color);
    }

    // Refractive
    if (mat->refractive) {
        Vector tmp_vector;
        Vector refracted;
        double n2;

        if (fabs(n1 - ETHER_INDEX_OF_REFRACTION) <= EPSILON) {
            n2 = 1.1;  // TODO: Hardcoded index of refraction for now
        } else {
            n2 = ETHER_INDEX_OF_REFRACTION;
        }
        double ratio = n1 / n2;

        double cos_theta_i = -1 * Vector_dot(&r.d, &norm);
        double cos_theta_t = sqrt(1 - (ratio*ratio * (1- cos_theta_i*cos_theta_i )));
        if (!isnan(cos_theta_t)) {
            Vector_scalar_mult(&refracted, &norm, ratio*cos_theta_i - cos_theta_t);
            if (cos_theta_i < 0) {
                Vector_scalar_mult(&refracted, &refracted, -1);
            }
            Vector_scalar_mult(&tmp_vector, &r.d, ratio);
            Vector_add(&refracted, &refracted, &tmp_vector);

            Vector_assign(&tmp_ray.o, &intersect);
            Vector_assign(&tmp_ray.d, &refracted);

            tmp_color = trace_ray(scene, &tmp_ray, depth+1, n2);
            Color_scalar_mult(&tmp_color, &tmp_color, mat->refractive);
            Color_add(&result, &result, &tmp_color);
        }

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
            if (dist < 100*EPSILON) {
                continue;
            }
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
