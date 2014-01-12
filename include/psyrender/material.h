
#ifndef _PSY_MATERIAL_H
#define _PSY_MATERIAL_H

#define MATERIAL_HEADER \
    struct material_func_table func; \

struct material_func_table {
    Color (*direction_scatter)(const Material* mat,
                               const SurfacePoint* sp,
                               const Photon* in,
                               const Ray* out);
    //PhotonList* (*Material_special_scatter)(const Material* mat,
    //                                        const SurfacePoint* sp,
    //                                        const Photon* in);
    //TODO: Implement random material sampling
    //Photon (*Material_random_scatter)(const Material* mat,
    //                                  const SurfacePoint* sp,
    //                                  const Photon* in);
    void (*free)(Material* mat);
};

struct Material_struct {
    MATERIAL_HEADER
};

/**
 * Get photon scattering given an incoming photon and an outgoing
 * direction.
 *
 * The surface point of the scattering is given as ``sp``. The incoming
 * direction and color of the photon is given as ``in``, while the outgoing
 * direction is given as ``out``.
 *
 * This function should return the same value if ``in->r`` and ``out``
 * are switched.
 *
 * One example in which this whould be used is to compute diffuse lighting
 * in a backwards ray tracer. When a ray hits the object, a ray must be
 * cast to each light source. The renderer would call this function to get
 * the amount of light scattered given the direction of the ray as well as
 * the light direction and color.
 */
#define Material_direction_scatter(m, ...) INTERFACE_CALL_FUNC(Material, direction_scatter, m, __VA_ARGS__)

/**
 * Get a list of high probability scattered photons, such as reflection or
 * refraction, given an incoming photon.
 *
 * The surface point of the scattering is given as ``sp``. The incoming
 * direction and color of the photon is given as ``in``. The returned
 * PhotonList must be free'd by the caller, along with the underlying
 * photon storage in the list.
 */
//#define Material_special_scatter(m, ...) INTERFACE_CALL_FURC(Material, special_scatter, m, __VA_ARGS__)

/**
 * Get a single random photon scattering given a random incoming photon.
 *
 * The surface point of the scattering is given as ``sp``. The incoming
 * direction and color of the photon is given as ``in``. The returned
 * photon should be pointing in a random direction in accordance with the
 * material's probability distribution function.
 */
//#define Material_random_scatter(m, ...) INTERFACE_CALL_FURC(Material, random_scatter, m, __VA_ARGS__)

#define Material_free(m) INTERFACE_CALL_FUNC_NO_ARGS(Material, free, m)

#include "materials/solid.h"
#include "materials/checker.h"

#endif
