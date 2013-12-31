
#include <stdlib.h>
#include <math.h>

#include "psyrender.h"


void Matrix4x4_print(Matrix4x4 m) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }
}

void Matrix4x4_set(Matrix4x4 m,
        double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33
) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;

    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;

    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;

    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

void Matrix4x4_set_identity(Matrix4x4 m) {
    Matrix4x4_set(m,
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

void Matrix4x4_set_zero(Matrix4x4 m) {
    Matrix4x4_set(m,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    );
}

void Matrix4x4_copy(Matrix4x4 out, Matrix4x4 m) {
    memcpy((void*) out, (void*) m, sizeof(Matrix4x4));
}

void Matrix4x4_multiply(Matrix4x4 out, Matrix4x4 m1, Matrix4x4 m2)
{
    Matrix4x4 m;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            m[i][j] = m1[i][0] * m2[0][j] +
                      m1[i][1] * m2[1][j] +
                      m1[i][2] * m2[2][j] +
                      m1[i][3] * m2[3][j];
        }
    }
    memcpy((void*) out, (void*) &m, sizeof(Matrix4x4));
}

void Matrix4x4_multiply_values(Matrix4x4 out, Matrix4x4 m1,
        double m2_00, double m2_01, double m2_02, double m2_03,
        double m2_10, double m2_11, double m2_12, double m2_13,
        double m2_20, double m2_21, double m2_22, double m2_23,
        double m2_30, double m2_31, double m2_32, double m2_33
) {
    Matrix4x4 m2;
    Matrix4x4_set(m2,
        m2_00, m2_01, m2_02, m2_03,
        m2_10, m2_11, m2_12, m2_13,
        m2_20, m2_21, m2_22, m2_23,
        m2_30, m2_31, m2_32, m2_33
    );
    Matrix4x4_multiply(out, m1, m2);
}

void Matrix4x4_premultiply_values(Matrix4x4 out,
        double m1_00, double m1_01, double m1_02, double m1_03,
        double m1_10, double m1_11, double m1_12, double m1_13,
        double m1_20, double m1_21, double m1_22, double m1_23,
        double m1_30, double m1_31, double m1_32, double m1_33,
        Matrix4x4 m2
) {
    Matrix4x4 m1;
    Matrix4x4_set(m1,
        m1_00, m1_01, m1_02, m1_03,
        m1_10, m1_11, m1_12, m1_13,
        m1_20, m1_21, m1_22, m1_23,
        m1_30, m1_31, m1_32, m1_33
    );
    Matrix4x4_multiply(out, m1, m2);
}

bool Matrix4x4_is_equal(Matrix4x4 m1, Matrix4x4 m2, double epsilon) {
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(fabs(m1[i][j] - m2[i][j]) > epsilon) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix4x4_is_identity(Matrix4x4 m, double epsilon) {
    Matrix4x4 identity;
    Matrix4x4_set_identity(identity);
    return Matrix4x4_is_equal(m, identity, epsilon);
}

/*
void Matrix4x4_inverse(Matrix4x4* out, const Matrix4x4* m) {
    //TODO: Not yet implemented
}
*/
