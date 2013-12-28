
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

/*
void Matrix4x4_inverse(Matrix4x4* out, const Matrix4x4* m) {
    //TODO: Not yet implemented
}
*/
