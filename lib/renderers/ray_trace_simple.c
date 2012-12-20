
#include "psyrender.h"

static Color trace_ray(Renderer_RayTraceSimple* renderer, const Scene* scene, const Ray* _r, unsigned int depth, double n1);
static Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect);

Renderer* Renderer_RayTraceSimple_new(unsigned int max_depth) {
    Renderer_RayTraceSimple* renderer = (Renderer_RayTraceSimple*) malloc(sizeof(Renderer_RayTraceSimple));
    renderer->func = renderer_raytracesimple_func_table;
    renderer->max_depth = max_depth;
    return (Renderer*) renderer;
}

bool Renderer_RayTraceSimple_render(Renderer* _renderer, Scene* scene, Camera* cam, Canvas* canvas) {
    Renderer_RayTraceSimple* renderer = (Renderer_RayTraceSimple*) _renderer;
    Color* row;
    Ray ray;

    Canvas_start(canvas);

    for (int y=canvas->height-1; y>=0; y--) {
        row = Canvas_get_next_row(canvas);
        for (int x=0; x<canvas->width; x++) {
            Camera_map(cam, ((double)x)/canvas->width, ((double)y)/canvas->height, &ray);
            row[x] = trace_ray(renderer, scene, &ray, 0, ETHER_INDEX_OF_REFRACTION);
        }
        Canvas_write_row(canvas, row);
    }

    Canvas_finish(canvas);
    return true;
}

static Color trace_ray(Renderer_RayTraceSimple* renderer, const Scene* scene, const Ray* _r, unsigned int depth, double n1) {
    Point intersect;
    Vector norm;
    Object* obj;
    Color result = {0, 0, 0};
    struct material_transmit transmit;
    Color tmp_color;
    Ray r, tmp_ray;

    Vector_assign(&r.o, &_r->o);
    Vector_assign(&r.d, &_r->d);
    Vector_normalize(&r.d);

    obj = ray_intersect(scene, &r, &intersect);

    if (!obj || depth > renderer->max_depth) {
        return (Color) {0, 0, 0};
    }

    Object_normal(obj, &intersect, &norm);
    transmit = Material_get_transmit(obj->mat, obj, &intersect);
    Vector_normalize(&norm);

    // Ambient
    result = transmit.ambient;

    // Diffuse
    Vector light_direction = {1, 0, 1}; // TODO: One hardcoded light for now
    Vector_normalize(&light_direction);

    tmp_ray.d = light_direction;
    tmp_ray.o = intersect;
    if (!ray_intersect(scene, &tmp_ray, NULL)) {

        double angle_factor = MAX(0, Vector_dot(&light_direction, &norm));
        Color_scalar_mult(&tmp_color, &transmit.diffuse, angle_factor);
        Color_add(&result, &result, &tmp_color);

        if (Object_inside(obj, &r.o)) {
            Vector_scalar_mult(&norm, &norm, -1);
        }

    }

    // Reflective
    if (!Color_is_black(&transmit.reflect)) {
        ray_reflect(&tmp_ray, &r, &intersect, &norm);
        tmp_color = trace_ray(renderer, scene, &tmp_ray, depth+1, n1);
        tmp_color = (Color) {
            tmp_color.r * (transmit.reflect.r / 255.0),
            tmp_color.g * (transmit.reflect.g / 255.0),
            tmp_color.b * (transmit.reflect.b / 255.0)
        };
        Color_add(&result, &result, &tmp_color);
    }

    // Refractive
    if (!Color_is_black(&transmit.refract)) {
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

            tmp_color = trace_ray(renderer, scene, &tmp_ray, depth+1, n2);
            Color_mult(&tmp_color, &tmp_color, &transmit.refract);
            Color_add(&result, &result, &tmp_color);
        }

    }

    return result;
}

static Object* ray_intersect(const Scene* scene, const Ray* r, Point* intersect) {
    Point obj_intersect, closest_intersect={INFINITY, INFINITY, INFINITY};
    double dist, closest_dist = INFINITY;
    Object* closest_obj = NULL;

    ListNode* node = scene->objects->head;
    while (node) {
        Object* obj = (Object*) node->data;

        if (Object_ray_intersect(obj, r, &obj_intersect)) {

            dist = Vector_dist_squared(&obj_intersect, &r->o);
            if (dist < 10*EPSILON) {
                node = node->next;
                continue;
            }
            if (dist < closest_dist) {
                closest_dist = dist;
                closest_intersect = obj_intersect;
                closest_obj = obj;
            }

        }

        node = node->next;
    }
    if (closest_obj != NULL && intersect) {
        *intersect = closest_intersect;
    }
    return closest_obj;
}
