
#ifndef _PSY_OBJECT_H
#define _PSY_OBJECT_H

struct Object_struct {

    // These pointers are not owned by the object, so when the object is
    // free'd, they are _not_ free'd with it.
    Shape* shape;   // Defines when light interacts with the object
    Material* mat;  // Defines how light interacts with the surface of the object
    Volume* vol;    // Defines how light interacts when inside the object

    // Object to world transformation
    // Defines rotations, translations, scales, etc. of the object's shape.
    //
    // Transforms are stored per object, not per shape. This way, many objects
    // can have the same shape, material or volume without any duplication.
    //
    // The object transform _is_ owned by the object, so it is free'd when the
    // object is free'd.
    Transform* trans;

};

// Create ObjectArray type
PTRARRAY_MAKE_HEADER(ObjectArray, Object)

/**
 * Return a new object with the given shape, material and volume.
 */
Object* Object_new(Shape* shape, Material* mat, Volume* volume);

/**
 * Returns true if the ray intersects with the object, false otherwise.
 *
 * If ``sp_out`` is not NULL, then the ``point``, ``normal``, ``u`` and ``v``
 * attributes of ``sp_out`` are filled in with the correct information for the
 * closest intersection found. Otherwise, ``sp_out`` remains untouched.
 *
 * The same as ``Shape_ray_intersect()``, but the Ray given and the
 * SurfacePoint returned are in world coordinates by converting to object
 * coordinates, calling ``Shape_ray_intersect()``, then converting the results
 * back to world coordinates.
*/
bool Object_ray_intersect(Object* o, const Ray* r, SurfacePoint* sp_out);

/**
 * Return true if the point is inside the object, false otherwise.
 *
 * The same as ``Shape_is_inside()``, but the point given is in world
 * coordinates, not object coordinates.
 */
bool Object_is_inside(const Object* o, const Point* p);

/**
 * Free the given object.
 *
 * Note that the shape, material and volume associated with the object are _not_
 * free'd with the object.
 */
void Object_free(Object* o);

#endif
