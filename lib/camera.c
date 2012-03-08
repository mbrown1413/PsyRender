
#include <stdlib.h>

#include "ray.h"

Camera* Camera_new() {
    return (Camera*) calloc(sizeof(Camera), 1);
}

void Camera_free(Camera* camera) {
    free(camera);
}
