
#include "psyrender.h"

#include <stdlib.h>
#include <math.h>

#define MAX_FOV PI-0.5

Camera_Basic* Camera_Basic_new(Point pos) {
    Camera_Basic* cam = (Camera_Basic*) malloc(sizeof(Camera_Basic));
    cam->func.map = Camera_Basic_map;
    cam->pos = pos;
    cam->forward = (Vector) {0, 1, 0};
    cam->up = (Vector) {0, 0, 1};
    cam->fov_x = 70 * (PI/180);
    cam->fov_y = 70 * (PI/180);
    //cam->fov_y = cam->fov_x * cam->image_height / cam->image_width;
    return cam;
}

void Camera_Basic_map(const Camera* _cam, double x, double y, Ray* ray) {
    Camera_Basic* cam = (Camera_Basic*) _cam;
    Vector right;
    Vector tmp;

    Vector_cross(&right, &cam->forward, &cam->up);
    Vector_normalize(&cam->forward);
    Vector_normalize(&cam->up);
    Vector_normalize(&right);

    // Convert x and y from range (0, 1) to (-1, 1)
    x = x*2 - 1;
    y = y*2 - 1;

    // Ray origin is at camera position
    Vector_assign(&ray->o, &cam->pos);

    // Left/right component of ray direction
    Vector_scalar_mult(&ray->d, &right, x*tan(cam->fov_x/2));

    // Up/down component of ray direction
    Vector_scalar_mult(&tmp, &cam->up, y*tan(cam->fov_y/2));
    Vector_add(&ray->d, &ray->d, &tmp);

    Vector_add(&ray->d, &ray->d, &cam->forward);

}

void Camera_Basic_zoom(Camera* _cam, double x, double y, double zoom_factor) {
    Camera_Basic* cam = (Camera_Basic*) _cam;
    Ray ray;
    const Vector const_up = (Vector) {0, 0, 1};

    Camera_map(cam, x, y, &ray);
    cam->forward = ray.d;

    // Make up perpendicular to forward
    Vector_cross(&cam->up, &const_up, &cam->forward);
    Vector_cross(&cam->up, &cam->forward, &cam->up);
    cam->fov_x /= zoom_factor;
    cam->fov_y /= zoom_factor;

    if (cam->fov_x >= MAX_FOV) cam->fov_x = MAX_FOV;
    if (cam->fov_y >= MAX_FOV) cam->fov_y = MAX_FOV;

}
