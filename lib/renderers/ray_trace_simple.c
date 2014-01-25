
#include <stdlib.h>
#include <float.h>

#include "psyrender.h"

static Color trace_ray(Renderer_RayTraceSimple* renderer, const Scene* scene, const Ray* _r, unsigned int depth, double n1);

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
    SurfacePoint sp;
    Color tmp_color, result = (Color) {0, 0, 0};
    Ray r;
    Photon p;

    Vector_assign(&r.o, &_r->o);
    Vector_assign(&r.d, &_r->d);
    Vector_normalize(&r.d);

    if(!Scene_ray_intersect(scene, &r, &sp) || depth > renderer->max_depth) {
        return (Color) {0, 0, 0};
    }
    Vector_normalize(&sp.norm);

    // Sample material in direction of lights
    for(int i=0; i<scene->lights->len; i++) {
        Light* light = LightList_GET(scene->lights, i);
        Photon light_photon = Light_sample(light, &sp.point);

        // Setup p.ray to point towards light for shadow ray
        p.ray.o = sp.point;
        Vector_scalar_mult(&p.ray.d, &light_photon.ray.d, -1);
        Vector_normalize(&p.ray.d);

        // Shadow Ray
        // Zero photon color if an object is blocking the light.
        //
        // The ray is not entirely ignored even if the shadow ray hits
        // something. This allows for non realistic materials that add ambient
        // light that does not depend on any light source.
        if(Scene_ray_intersect(scene, &p.ray, NULL)) {
            light_photon.color = (Color) {0, 0, 0};
        }

        // Add material's scatter when the photon hits it
        tmp_color = Material_direction_scatter(sp.obj->mat, &sp, &light_photon, &r);
        Color_add(&result, &result, &tmp_color);

    }

    // Special rays (reflection and refraction)
    p.ray = r;
    p.color = (Color) {255, 255, 255};
    PhotonList* photons = Material_special_scatter(sp.obj->mat, &sp, &p);
    for(int i=0; i<photons->len; i++) {
        Photon* photon_p = PhotonList_GET(photons, i);
        tmp_color = trace_ray(renderer, scene, &photon_p->ray, depth+1, n1);
        Color_mult(&tmp_color, &tmp_color, &photon_p->color);
        Color_add(&result, &result, &tmp_color);
        free(photon_p);
    }

    return result;
}
