#ifndef _PSY_TRANSFORM_H
#define _PSY_TRANSFORM_H

typedef struct {
    Matrix4x4 m;
    Matrix4x4 inv;
} Transform;

Transform* Transform_new();
//void Transform_copy(Transform* out, const Transform* t);
void Transform_free(Transform* t);

void Transform_matrix(Transform* t, Matrix4x4 m, Matrix4x4 m_inv);
void Transform_translate(Transform* t, double x, double y, double z);
//void Transform_rotate(Transform* t, double axis_x, double axis_y, double axis_z, double degrees);
void Transform_rotate_x(Transform* t, double degrees);
void Transform_rotate_y(Transform* t, double degrees);
void Transform_rotate_z(Transform* t, double degrees);
void Transform_scale(Transform* t, double x, double y, double z);

void Transform_point(const Transform* t, Point* out, const Point* p);
void Transform_vector(const Transform* t, Vector* out, const Vector* v);
void Transform_normal(const Transform* t, Vector* out, const Vector* v);
void Transform_ray(const Transform* t, Ray* out, const Ray* in);

#endif
