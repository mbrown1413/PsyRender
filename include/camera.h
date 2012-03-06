
#ifndef _RAY_CAMERA_H
#define _RAY_CAMERA_H

typedef struct {

    // Up direction with origin at eye center
    Ray up;

    // Orientation in radians
    double pitch;
    double yaw;
    double roll;

    double fov;  // Radians

    /*
    // These two points define the square that the camera looks through
    Point viewport_pt1;  // Top left of the image
    Point viewport_pt2;  // Bottom right of the image
    */

    // Image size
    unsigned int width;
    unsigned int height;

} Camera;

Camera* Camera_new();
void Camera_free(Camera* camera);

#endif
