
#ifndef _RAY_CAMERA_BASIC_H
#define _RAY_CAMERA_BASIC_H

typedef struct {
    CAMERA_HEADER
    Vector up;
    Vector forward;
    double fov_x, fov_y;
} Camera_Basic;

Camera_Basic* Camera_Basic_new();
void Camera_Basic_render(const Scene* scene, const Camera* _cam, Canvas* canvas);
void Camera_Basic_zoom(Camera* cam, unsigned int x, unsigned int y, double zoom_factor);

#endif
