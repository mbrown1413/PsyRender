
#include "psyrender.h"

#include "test.h"

int test_multiply();
int test_equal();
int test_copy();

test_func_t test_functions[] = {
    test_multiply,
    test_equal,
    test_copy,
    NULL
};

int main() {
    return test_main(test_functions);
}


int test_multiply() {
    Matrix4x4 m1, m2, correct_result, result;
    Matrix4x4_set(m1,
         38, -88, -55,  95,
         52,  87,  40, -64,
        -62,  11,  91, -41,
        -98,  64,   4,  12
    );
    Matrix4x4_set(m2,
        -53,  62,  70,  -45,
         42, -93, -80,   45,
        -83,  -5, -32, -100,
         37,  83, -55,  -89
    );
    Matrix4x4_set(correct_result,
         2370,  18700,   6235, -8625,
        -4790, -10379,  -1080,  3271,
        -5322,  -8725,  -5877, -2166,
         7994, -11052, -12768,  5822
    );

    Matrix4x4_multiply(result, m1, m2);
    ASSERT(Matrix4x4_is_equal(result, correct_result, 0));

    Matrix4x4_set_zero(result);
    Matrix4x4_multiply_values(result, m1,
        m2[0][0], m2[0][1], m2[0][2], m2[0][3],
        m2[1][0], m2[1][1], m2[1][2], m2[1][3],
        m2[2][0], m2[2][1], m2[2][2], m2[2][3],
        m2[3][0], m2[3][1], m2[3][2], m2[3][3]
    );
    ASSERT(Matrix4x4_is_equal(result, correct_result, 0));

    return TEST_PASS;
}

int test_equal() {
    Matrix4x4 m1, m2, m3, m4;
    Matrix4x4_set(m1,
         38, -88, -55,  95,
         52,  87,  40, -64,
        -62,  11,  91, -41,
        -98,  64,   4,  12
    );
    Matrix4x4_set(m2,  // Same as m1
         38, -88, -55,  95,
         52,  87,  40, -64,
        -62,  11,  91, -41,
        -98,  64,   4,  12
    );
    Matrix4x4_set(m3,  // Completely different than m1
         39, -87, -54,  96,
         53,  88,  41, -63,
        -61,  12,  92, -40,
        -97,  65,   5,  13
    );
    Matrix4x4_set(m4,  // m3[3][3] different than m1
         38, -88, -55,  95,
         52,  87,  40, -64,
        -62,  11,  91, -41,
        -98,  64,   4,   0
    );

    ASSERT(Matrix4x4_is_equal(m1, m2, 0));
    ASSERT(!Matrix4x4_is_equal(m1, m3, 0));
    ASSERT(!Matrix4x4_is_equal(m1, m4, 0));
    ASSERT(!Matrix4x4_is_equal(m2, m3, 0));
    ASSERT(!Matrix4x4_is_equal(m2, m4, 0));
    ASSERT(!Matrix4x4_is_equal(m3, m4, 0));
    return TEST_PASS;
}

int test_copy() {
    Matrix4x4 m1, m2;
    Matrix4x4_set(m1,
         38, -88, -55,  95,
         52,  87,  40, -64,
        -62,  11,  91, -41,
        -98,  64,   4,  12
    );
    Matrix4x4_copy(m2, m1);
    ASSERT(Matrix4x4_is_equal(m1, m2, 0));
    return TEST_PASS;
}
