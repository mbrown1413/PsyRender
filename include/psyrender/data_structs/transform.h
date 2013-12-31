/**
 * A transform is a mapping from one coordinate space to another. It is
 * represented by a 4x4 matrix and, for efficiency, the inverse of that 4x4
 * matrix. It can be used to transform things such as points and rays.
 *
 * A new identity transform is created with ``Transform_new()``.
 *
 * To modify the transform, use functions with transformation verbs, like
 * ``Transform_translate()`` to translate, or ``Transform_rotate_x()`` to
 * rotate about the x axis. These functions post-multiply a matrix to the
 * current matrix. Thus, each transformation is always done in the original
 * coordinate system (world coordinates). For example: ``Transform_rotate_x()``
 * will always rotate about the x axis centered about (0, 0, 0), even if
 * previous transforms have been applied. Arbitrary transforms can be done with
 * ``Transform_matrix_multiply()``.
 *
 * To apply transformations, use functions like ``Transform_point()`` and
 * ``Transform_vector()``.
 */

#ifndef _PSY_TRANSFORM_H
#define _PSY_TRANSFORM_H

typedef struct {
    Matrix4x4 m;
    Matrix4x4 inv;
} Transform;

/**
 * Create a new identity transform.
 *
 * The resulting transform won't actually change anything when transforming
 * something. Use functions such as ``Transform_translate()`` to modify the
 * transform.
 *
 * Free a transform with Transform_free().
 */
Transform* Transform_new();

/**
 * Copy transform ``t`` to ``out``.
 */
void Transform_copy(Transform* out, const Transform* t);

/**
 * Free transform ``t``.
 */
void Transform_free(Transform* t);

/**
 * Multiplies a transform matrix with ``m``.
 *
 * ``m_inv`` must be the inverse of ``m``, or the transform may not work
 * properly.
 */
void Transform_matrix_multiply(Transform* t, Matrix4x4 m, Matrix4x4 m_inv);

/**
 * Translate the transform by vector (x, y, z).
 */
void Transform_translate(Transform* t, double x, double y, double z);

//void Transform_rotate(Transform* t, double axis_x, double axis_y, double axis_z, double degrees);

/**
 * Rotates the transform about the x axis.
 *
 * If the x axis is pointing towards the viewer, this will rotate counter
 * clockwise.
 */
void Transform_rotate_x(Transform* t, double degrees);

/**
 * Rotates the transform about the y axis.
 *
 * If the y axis is pointing towards the viewer, this will rotate counter
 * clockwise.
 */
void Transform_rotate_y(Transform* t, double degrees);

/**
 * Rotates the transform about the z axis.
 *
 * If the z axis is pointing towards the viewer, this will rotate counter
 * clockwise.
 */
void Transform_rotate_z(Transform* t, double degrees);

/**
 * Scales the transform about (0, 0, 0) in each axis. If ``x``, ``y``, and
 * ``z`` are not equal, the transform will be stretched.
 */
void Transform_scale(Transform* t, double x, double y, double z);

/**
 * Apply the transform to a point.
 */
void Transform_point(const Transform* t, Point* out, const Point* p);

/**
 * Apply the transform to a vector.
 */
void Transform_vector(const Transform* t, Vector* out, const Vector* v);

/**
 * Apply the transform to a normal.
 *
 * Note that normals are transformed differently than vectors.
 */
void Transform_normal(const Transform* t, Vector* out, const Vector* v);

/**
 * Apply the transform to a ray.
 */
void Transform_ray(const Transform* t, Ray* out, const Ray* in);

/**
 * Apply the inverse transformation to a point.
 */
void Transform_point_inverse(const Transform* t, Point* out, const Point* p);

/**
 * Apply the inverse transformation to a vector.
 */
void Transform_vector_inverse(const Transform* t, Vector* out, const Vector* v);

/**
 * Apply the inverse transformation to a normal.
 *
 * Note that normals are transformed differently than vectors.
 */
void Transform_normal_inverse(const Transform* t, Vector* out, const Vector* v);

/**
 * Apply the inverse transformation to a ray.
 */
void Transform_ray_inverse(const Transform* t, Ray* out, const Ray* in);

#endif
