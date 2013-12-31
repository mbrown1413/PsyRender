
#include "psyrender.h"

#include "test.h"

const double epsilon = 10E-10;

// Asserts that the inverse transform is actually the inverse
#define ASSERT_TRANSFORM_INVERSE(t) { \
    Matrix4x4 _m; \
    Matrix4x4_multiply(_m, t->m, t->inv); \
    ASSERT(Matrix4x4_is_identity(_m, epsilon)); \
}

int test_null_transform();
int test_translate();
int test_rotate();
int test_rotate_x();
int test_rotate_y();
int test_rotate_z();
int test_scale_xyz();
int test_scale_y();
int test_translate_rotate();
int test_copy();

test_func_t test_functions[] = {
    test_null_transform,
    test_translate,
    test_rotate,
    test_rotate_x,
    test_rotate_y,
    test_rotate_z,
    test_scale_xyz,
    test_scale_y,
    test_translate_rotate,
    test_copy,
    NULL
};

int main() {
    return test_main(test_functions);
}

/**
 * Transforms ``point``, ``vector``, ``normal`` and ``ray`` using transform
 * ``t`` and makes sure the results match the ``correct_*`` arguments.
 */
int assert_transform_results(const Transform* t,
                             // Inputs to transform
                             Point point,
                             Vector vector,
                             Vector normal,
                             Ray ray,

                             // Correct results when transform is applied to input 
                             Point correct_point,
                             Vector correct_vector,
                             Vector correct_normal,
                             Ray correct_ray
) {
    Point p_out, p_out2;
    Vector v_out, v_out2;
    Vector n_out, n_out2;
    Ray r_out, r_out2;

    // For point, vector, normal and ray, store forward transformation in ?_out
    // and the inverse transformation of ?_out into ?_out2.

    Transform_point(t, &p_out, &point);
    Transform_point_inverse(t, &p_out2, &p_out);

    Transform_vector(t, &v_out, &vector);
    Transform_vector_inverse(t, &v_out2, &v_out);

    // Normals might have incorrect scale, since the inverse transform is used
    // for normal transformation. Here we ignore scale by normalizing ``n_out``
    // and ``correct_normal``.
    Transform_normal(t, &n_out, &normal);
    Transform_normal_inverse(t, &n_out2, &n_out);
    Vector_normalize(&n_out);
    Vector_normalize(&correct_normal);

    Transform_ray(t, &r_out, &ray);
    Transform_ray_inverse(t, &r_out2, &r_out);

    // Forward transformation ASSERTs
    ASSERT(Point_is_equal(&p_out, &correct_point, epsilon));
    ASSERT(Vector_is_equal(&v_out, &correct_vector, epsilon));
    ASSERT(Vector_is_equal(&n_out, &correct_normal, epsilon));
    ASSERT(Ray_is_equal(&r_out, &correct_ray, epsilon));

    // Inverse transformation ASSERTs
    ASSERT(Point_is_equal(&p_out2, &point, epsilon));
    ASSERT(Vector_is_equal(&v_out2, &vector, epsilon));
    ASSERT(Vector_is_equal(&n_out2, &normal, epsilon));
    ASSERT(Ray_is_equal(&r_out2, &ray, epsilon));

    return TEST_PASS;
}


int test_null_transform() {
    Point p = {1, 1, 1};
    Vector v = {1, 1, 1};
    Vector n = {1, 1, 1};  // Normal
    Ray r = {{1, 1, 1}, {1, 1, 1}};

    Transform* t = Transform_new();
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p, v, n, r
    );

    Transform_free(t);
    return result;
}

int test_translate() {
    Point p = {1, 1, 1};
    Vector v = {1, 1, 1};
    Vector n = {1, 1, 1};  // Normal
    Ray r = {{1, 1, 1}, {1, 1, 1}};

    Point p_correct = {2, 2, 2};
    Vector v_correct = {1, 1, 1};
    Vector n_correct = {1, 1, 1};
    Ray r_correct = {{2, 2, 2}, {1, 1, 1}};

    Transform* t = Transform_new();
    Transform_translate(t, 1, 1, 1);
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p_correct, v_correct, n_correct, r_correct
    );

    Transform_free(t);
    return result;
}

int test_rotate() {
    return TEST_SKIP;
}

int test_rotate_x() {
    Point p = {0, 1, 1};
    Vector v = {0, 1, 1};
    Vector n = {0, 1, 1};  // Normal
    Ray r = {{0, 1, 0}, {0, 0, 1}};

    Point p_correct = {0, 1, -1};
    Vector v_correct = {0, 1, -1};
    Vector n_correct = {0, 1, -1};
    Ray r_correct = {{0, 0, -1}, {0, 1, 0}};

    Transform* t = Transform_new();
    Transform_rotate_x(t, -90);
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p_correct, v_correct, n_correct, r_correct
    );

    Transform_free(t);
    return result;
}

int test_rotate_y() {
    Point p = {1, 0, 1};
    Vector v = {1, 0, 1};
    Vector n = {1, 0, 1};  // Normal
    Ray r = {{0, 0, 1}, {1, 0, 0}};

    Point p_correct = {-1, 0, 1};
    Vector v_correct = {-1, 0, 1};
    Vector n_correct = {-1, 0, 1};
    Ray r_correct = {{-1, 0, 0}, {0, 0, 1}};

    Transform* t = Transform_new();
    Transform_rotate_y(t, -90);
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p_correct, v_correct, n_correct, r_correct
    );

    Transform_free(t);
    return result;
}

int test_rotate_z() {
    Point p = {1, 1, 0};
    Vector v = {1, 1, 0};
    Vector n = {1, 1, 0};  // Normal
    Ray r = {{0, 1, 0}, {1, 0, 0}};

    Point p_correct = {1, -1, 0};
    Vector v_correct = {1, -1, 0};
    Vector n_correct = {1, -1, 0};
    Ray r_correct = {{1, 0, 0}, {0, -1, 0}};

    Transform* t = Transform_new();
    Transform_rotate_z(t, -90);
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p_correct, v_correct, n_correct, r_correct
    );

    Transform_free(t);
    return result;
}

int test_scale_xyz() {
    Point p = {1, 1, 1};
    Vector v = {1, 1, 1};
    Vector n = {1, 1, 1};  // Normal
    Ray r = {{1, 1, 1}, {1, 1, 1}};

    Point p_correct = {2, 2, 2};
    Vector v_correct = {2, 2, 2};
    Vector n_correct = {2, 2, 2};
    Ray r_correct = {{2, 2, 2}, {2, 2, 2}};

    Transform* t = Transform_new();
    Transform_scale(t, 2, 2, 2);
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p_correct, v_correct, n_correct, r_correct
    );

    Transform_free(t);
    return result;
}

/**
 * Normal transforms are different than vector transforms when a scale
 * transform is performed unevenly across the x, y, and z axes.
 */
int test_scale_y() {
    Point p = {1, 1, 1};
    Vector v = {1, 1, 1};
    Vector n = {1, 1, 1};  // Normal
    Ray r = {{1, 1, 1}, {1, 1, 1}};

    Point p_correct = {1, 0.5, 1};
    Vector v_correct = {1, 0.5, 1};
    Vector n_correct = {0.5, 1, 0.5};
    Ray r_correct = {{1, 0.5, 1}, {1, 0.5, 1}};

    Transform* t = Transform_new();
    Transform_scale(t, 1, 0.5, 1);
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p_correct, v_correct, n_correct, r_correct
    );

    Transform_free(t);
    return result;
}

int test_translate_rotate() {
    Point p = {0, 1, 0};
    Vector v = {0, 1, 0};
    Vector n = {0, 1, 0};  // Normal
    Ray r = {{0, 1, 0}, {0, 1, 0}};

    Point p_correct = {0, 1, 1};
    Vector v_correct = {-1, 0, 0};
    Vector n_correct = {-1, 0, 0};
    Ray r_correct = {{0, 1, 1}, {-1, 0, 0}};

    Transform* t = Transform_new();
    Transform_translate(t, 1, 1, 1);
    ASSERT_TRANSFORM_INVERSE(t);
    Transform_rotate_z(t, 90);
    ASSERT_TRANSFORM_INVERSE(t);

    int result = assert_transform_results(t,
        p, v, n, r,
        p_correct, v_correct, n_correct, r_correct
    );

    Transform_free(t);
    return result;
}

int test_copy() {
    Transform* t1 = Transform_new();
    Transform_translate(t1, 1, 1, 1);
    Transform_rotate_x(t1, 45);

    Transform* t2 = Transform_new();
    Transform_copy(t2, t1);

    ASSERT(Matrix4x4_is_equal(t1->m, t2->m, 0));
    ASSERT(Matrix4x4_is_equal(t1->inv, t2->inv, 0));

    Transform_free(t1);
    Transform_free(t2);
    return TEST_PASS;
}
