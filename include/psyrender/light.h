#ifndef _PSY_LIGHT_H
#define _PSY_LIGHT_H

struct Light_struct {
    Point p;
    Color c;
};

// Create LightList type
PTRLIST_MAKE_HEADER(LightList, Light)

/**
 * Return new light source with the given color at the given point.
 */
Light* Light_new(Point p, Color c);

/**
 * Return a photon traveling from the light source towards the given point.
 */
Photon Light_sample(const Light* l, const Point* p);

/**
 * Free light source allocated with ``Light_new()``.
 */
void Light_free(Light* l);

#endif
