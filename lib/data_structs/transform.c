
#include "psyrender.h"

Transform* Transform_new() {
    Transform* t = malloc(sizeof(Transform));
    Matrix4x4_set_identity(t->m);
    Matrix4x4_set_identity(t->inv);
    return t;
}

void Transform_copy(Transform* out, const Transform* t) {
    memcpy((void*) out, (void*) t, sizeof(Transform));
}

void Transform_free(Transform* t) {
    free(t);
}

void Transform_matrix_multiply(Transform* t, Matrix4x4 m, Matrix4x4 m_inv) {
    Matrix4x4_multiply(t->m, t->m, m);
    Matrix4x4_multiply(t->inv, t->inv, m_inv);
}

void Transform_translate(Transform* t, double x, double y, double z) {
    Matrix4x4_multiply_values(t->m, t->m,
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
    Matrix4x4_premultiply_values(t->inv,
        1, 0, 0, -x,
        0, 1, 0, -y,
        0, 0, 1, -z,
        0, 0, 0,  1,
        t->inv
    );
}

//void Transform_rotate(Transform* t, double axis_x, double axis_y, double axis_z, double degrees);

void Transform_rotate_x(Transform* t, double degrees) {
    double radians = degrees * PI/180;
    double s = sin(radians);
    double c = cos(radians);
    Matrix4x4_multiply_values(t->m, t->m,
        1, 0,  0, 0,
        0, c, -s, 0,
        0, s,  c, 0,
        0, 0,  0, 1
    );
    Matrix4x4_premultiply_values(t->inv,
        1,  0, 0, 0,
        0,  c, s, 0,
        0, -s, c, 0,
        0,  0, 0, 1,
        t->inv
    );
}

void Transform_rotate_y(Transform* t, double degrees) {
    double radians = degrees * PI/180;
    double s = sin(radians);
    double c = cos(radians);
    Matrix4x4_multiply_values(t->m, t->m,
         c, 0, s, 0,
         0, 1, 0, 0,
        -s, 0, c, 0,
         0, 0, 0, 1
    );
    Matrix4x4_premultiply_values(t->inv,
        c, 0, -s, 0,
        0, 1,  0, 0,
        s, 0,  c, 0,
        0, 0,  0, 1,
        t->inv
    );
}

void Transform_rotate_z(Transform* t, double degrees) {
    double radians = degrees * PI/180;
    double s = sin(radians);
    double c = cos(radians);
    Matrix4x4_multiply_values(t->m, t->m,
        c, -s, 0, 0,
        s,  c, 0, 0,
        0,  0, 1, 0,
        0,  0, 0, 1
    );
    Matrix4x4_premultiply_values(t->inv,
         c, s, 0, 0,
        -s, c, 0, 0,
         0, 0, 1, 0,
         0, 0, 0, 1,
        t->inv
    );
}

void Transform_scale(Transform* t, double x, double y, double z) {
    Matrix4x4_multiply_values(t->m, t->m,
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
    Matrix4x4_premultiply_values(t->inv,
        1/x,   0,   0, 0,
          0, 1/y,   0, 0,
          0,   0, 1/z, 0,
          0,   0,   0, 1,
        t->inv
    );
}

void Transform_point(const Transform* t, Point* out, const Point* p) {
    double w = t->m[3][0]*p->x + t->m[3][1]*p->y + t->m[3][2]*p->z + t->m[3][3];
    if(w == 1) {
        out->x = t->m[0][0]*p->x + t->m[0][1]*p->y + t->m[0][2]*p->z + t->m[0][3];
        out->y = t->m[1][0]*p->x + t->m[1][1]*p->y + t->m[1][2]*p->z + t->m[1][3];
        out->z = t->m[2][0]*p->x + t->m[2][1]*p->y + t->m[2][2]*p->z + t->m[2][3];
    } else {
        out->x = (t->m[0][0]*p->x + t->m[0][1]*p->y + t->m[0][2]*p->z + t->m[0][3]) / w;
        out->y = (t->m[1][0]*p->x + t->m[1][1]*p->y + t->m[1][2]*p->z + t->m[1][3]) / w;
        out->z = (t->m[2][0]*p->x + t->m[2][1]*p->y + t->m[2][2]*p->z + t->m[2][3]) / w;
    }
}

void Transform_vector(const Transform* t, Vector* out, const Vector* v) {
    out->x = t->m[0][0]*v->x + t->m[0][1]*v->y + t->m[0][2]*v->z;
    out->y = t->m[1][0]*v->x + t->m[1][1]*v->y + t->m[1][2]*v->z;
    out->z = t->m[2][0]*v->x + t->m[2][1]*v->y + t->m[2][2]*v->z;
}

void Transform_normal(const Transform* t, Vector* out, const Vector* v) {
    // Set ``out`` to the v times the transpose of the inverse
    out->x = t->inv[0][0]*v->x + t->inv[1][0]*v->y + t->inv[2][0]*v->z;
    out->y = t->inv[0][1]*v->x + t->inv[1][1]*v->y + t->inv[2][1]*v->z;
    out->z = t->inv[0][2]*v->x + t->inv[1][2]*v->y + t->inv[2][2]*v->z;
}

void Transform_ray(const Transform* t, Ray* out, const Ray* in) {
    Transform_point(t, &out->o, &in->o);
    Transform_vector(t, &out->d, &in->d);
}

void Transform_point_inverse(const Transform* t, Point* out, const Point* p) {
    double w = t->inv[3][0]*p->x + t->inv[3][1]*p->y + t->inv[3][2]*p->z + t->inv[3][3];
    if(w == 1) {
        out->x = t->inv[0][0]*p->x + t->inv[0][1]*p->y + t->inv[0][2]*p->z + t->inv[0][3];
        out->y = t->inv[1][0]*p->x + t->inv[1][1]*p->y + t->inv[1][2]*p->z + t->inv[1][3];
        out->z = t->inv[2][0]*p->x + t->inv[2][1]*p->y + t->inv[2][2]*p->z + t->inv[2][3];
    } else {
        out->x = (t->inv[0][0]*p->x + t->inv[0][1]*p->y + t->inv[0][2]*p->z + t->inv[0][3]) / w;
        out->y = (t->inv[1][0]*p->x + t->inv[1][1]*p->y + t->inv[1][2]*p->z + t->inv[1][3]) / w;
        out->z = (t->inv[2][0]*p->x + t->inv[2][1]*p->y + t->inv[2][2]*p->z + t->inv[2][3]) / w;
    }
}

void Transform_vector_inverse(const Transform* t, Vector* out, const Vector* v) {
    out->x = t->inv[0][0]*v->x + t->inv[0][1]*v->y + t->inv[0][2]*v->z;
    out->y = t->inv[1][0]*v->x + t->inv[1][1]*v->y + t->inv[1][2]*v->z;
    out->z = t->inv[2][0]*v->x + t->inv[2][1]*v->y + t->inv[2][2]*v->z;
}

void Transform_normal_inverse(const Transform* t, Vector* out, const Vector* v) {
    // Set ``out`` to the v times the transpose of the inverse
    out->x = t->m[0][0]*v->x + t->m[1][0]*v->y + t->m[2][0]*v->z;
    out->y = t->m[0][1]*v->x + t->m[1][1]*v->y + t->m[2][1]*v->z;
    out->z = t->m[0][2]*v->x + t->m[1][2]*v->y + t->m[2][2]*v->z;
}

void Transform_ray_inverse(const Transform* t, Ray* out, const Ray* in) {
    Transform_point_inverse(t, &out->o, &in->o);
    Transform_vector_inverse(t, &out->d, &in->d);
}
