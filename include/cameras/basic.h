
#ifndef _RAY_CAMERA_BASIC_H
#define _RAY_CAMERA_BASIC_H

typedef struct {
    CAMERA_HEADER
    Vector up;
    Vector forward;
    double fov_x, fov_y;
} Camera_Basic;

Camera_Basic* Camera_Basic_new(Point pos);
void Camera_Basic_map(const Camera* _cam, double x, double y, Ray* ray);
void Camera_Basic_zoom(Camera* cam, double x, double y, double zoom_factor);

#endif
