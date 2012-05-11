
#include "ray.h"

#include <stdlib.h>
#include <math.h>

#define MAX_FOV PI-0.5

Camera_Basic* Camera_Basic_new(unsigned int image_width, unsigned int image_height, Point pos) {
    Camera_Basic* cam = (Camera_Basic*) malloc(sizeof(Camera_Basic));
    cam->func.render = Camera_Basic_render;
    cam->image_width = image_width;
    cam->image_height = image_height;
    cam->pos = pos;
    cam->forward = (Vector) {0, 1, 0};
    cam->up = (Vector) {0, 0, 1};
    cam->fov_x = 70 * (PI/180);
    cam->fov_y = cam->fov_x * cam->image_height / cam->image_width;
    return cam;
}

void Camera_Basic_render(const Scene* scene, const Camera* _cam, Canvas* canvas) {
    Camera_Basic* cam = (Camera_Basic*) _cam;
    Color* row;
    Ray ray;
    Vector left;
    Vector delta_x, delta_y;  // Amount ray will change when moving one x or y in the image

    Vector_cross(&left, &cam->up, &cam->forward);
    Vector_normalize(&left);

    Vector_normalize(&cam->forward);

    ray.o.x = cam->pos.x;
    ray.o.y = cam->pos.y;
    ray.o.z = cam->pos.z;

    Vector_scalar_mult(&delta_x, &left, -2*tan(cam->fov_x/2) / cam->image_width);
    Vector_scalar_mult(&delta_y, &cam->up, -2*tan(cam->fov_y/2) / cam->image_height);

    // Point ray towards upper left pixel of image
    ray.d.x = cam->forward.x - (delta_x.x * cam->image_width/2.0) - (delta_y.x * cam->image_height/2.0);
    ray.d.y = cam->forward.y - (delta_x.y * cam->image_width/2.0) - (delta_y.y * cam->image_height/2.0);
    ray.d.z = cam->forward.z - (delta_x.z * cam->image_width/2.0) - (delta_y.z * cam->image_height/2.0);

    for (int y=0; y<cam->image_height; y++) {
        row = Canvas_get_next_row(canvas, (Camera*)cam, y);
        for (int x=0; x<cam->image_width; x++) {

            row[x] = trace_ray_priv(scene, &ray, 0, ETHER_INDEX_OF_REFRACTION);

            ray.d.x += delta_x.x;
            ray.d.y += delta_x.y;
            ray.d.z += delta_x.z;

        }
        Canvas_finish_row(canvas, row);

        ray.d.x += delta_y.x - delta_x.x*cam->image_width;
        ray.d.y += delta_y.y - delta_x.y*cam->image_width;
        ray.d.z += delta_y.z - delta_x.z*cam->image_width;

    }
}

void Camera_Basic_zoom(Camera* _cam, unsigned int x, unsigned int y, double zoom_factor) {
    Camera_Basic* cam = (Camera_Basic*) _cam;
    Vector left;
    Vector delta_x, delta_y;  // Amount ray will change when moving one x or y in the image

    double right_pan = (x - cam->image_width/2.0) / (cam->image_width/2.0);
    double down_pan = (y - cam->image_width/2.0) / (cam->image_height/2.0);

    Vector_cross(&left, &cam->up, &cam->forward);
    Vector_normalize(&left);

    Vector_normalize(&cam->forward);

    Vector_scalar_mult(&delta_x, &left, -2*tan(cam->fov_x/2) / cam->image_width);
    Vector_scalar_mult(&delta_y, &cam->up, -2*tan(cam->fov_y/2) / cam->image_height);

    // Point camera towards x, y (image coordinates)
    cam->forward.x = cam->forward.x + right_pan*(delta_x.x * cam->image_width/2.0) + down_pan*(delta_y.x * cam->image_height/2.0);
    cam->forward.y = cam->forward.y + right_pan*(delta_x.y * cam->image_width/2.0) + down_pan*(delta_y.y * cam->image_height/2.0);
    cam->forward.z = cam->forward.z + right_pan*(delta_x.z * cam->image_width/2.0) + down_pan*(delta_y.z * cam->image_height/2.0);

    cam->fov_x /= zoom_factor;
    cam->fov_y /= zoom_factor;

    if (cam->fov_x >= MAX_FOV) cam->fov_x = MAX_FOV;
    if (cam->fov_y >= MAX_FOV) cam->fov_y = MAX_FOV;
}
