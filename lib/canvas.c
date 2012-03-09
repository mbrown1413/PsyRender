
#include <string.h>

#include "ray.h"

void Canvas_set_error(Canvas* canvas, char* error) {
    strcpy(canvas->error_str, error);
}
