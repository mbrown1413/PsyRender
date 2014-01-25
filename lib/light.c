#include <stdlib.h>

#include "psyrender.h"

Light* Light_new(Point point, Color color) {
    Light* l = (Light*) malloc(sizeof(Light));
    l->p = point;
    l->c = color;
    return l;
}

/**
 * Return a photon traveling from the light source towards the given point.
 */
Photon Light_sample(const Light* l, const Point* point) {
    Photon photon;
    photon.ray.o = *point;
    Vector_subtract(&photon.ray.d, point, &l->p);
    Vector_normalize(&photon.ray.d);
    photon.color = l->c;
    return photon;
}

/**
 * Free light source allocated with ``Light_new()``.
 */
void Light_free(Light* l) {
    free(l);
}
