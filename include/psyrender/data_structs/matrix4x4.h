/**
 * A 4x4 matrix implementation.
 *
 * Matrices are stored in row major order as a two dimmensional double array.
 * Note that, since the matrix type is itself an array, matrices are passed by
 * reference even though Matrix4x4_* function arguments are are of type
 * Matrix4x4, not Matrix4x4*.
 */

#ifndef _PSY_MATRIX4X4_H
#define _PSY_MATRIX4X4_H

typedef double Matrix4x4[4][4];

/**
 * Print matrix ``m``.
 */
void Matrix4x4_print(Matrix4x4 m);

/**
 * Sets values of matrix ``m``.
 */
void Matrix4x4_set(Matrix4x4 m,
        double m00, double m01, double m02, double m03,
        double m10, double m11, double m12, double m13,
        double m20, double m21, double m22, double m23,
        double m30, double m31, double m32, double m33
);

/**
 * Set matix to identity matrix.
 */
void Matrix4x4_set_identity(Matrix4x4 m);

/**
 * Set matrix to zero matrix;
 */
void Matrix4x4_set_zero(Matrix4x4 m);

/**
 * Copy matrix ``m`` to ``out``.
 */
void Matrix4x4_copy(Matrix4x4 out, Matrix4x4 m);

/**
 * Multiply matrices ``m1`` with ``m2``, store the result in ``out``.
 */
void Matrix4x4_multiply(Matrix4x4 out, Matrix4x4 m1, Matrix4x4 m2);

/**
 * Like ``Matrix4x4_multiply``, but values for m2 are passed individually.
 */
void Matrix4x4_multiply_values(Matrix4x4 out, Matrix4x4 m1,
        double m2_00, double m2_01, double m2_02, double m2_03,
        double m2_10, double m2_11, double m2_12, double m2_13,
        double m2_20, double m2_21, double m2_22, double m2_23,
        double m2_30, double m2_31, double m2_32, double m2_33
);

/**
 * Like ``Matrix4x4_multiply_values``, but individual values are given for m1,
 * not m2.  m1*m2 is returned.
 */
void Matrix4x4_premultiply_values(Matrix4x4 out,
        double m1_00, double m1_01, double m1_02, double m1_03,
        double m1_10, double m1_11, double m1_12, double m1_13,
        double m1_20, double m1_21, double m1_22, double m1_23,
        double m1_30, double m1_31, double m1_32, double m1_33,
        Matrix4x4 m2
);

/**
 * Test equality of matrices ``m1`` and ``m2`` with tolerance ``epsilon``.
 *
 * The matrices are compared element by element. If all ``m1[i][j]`` and
 * ``m2[i][j]`` are within ``epsilon`` of eachother, ``true`` is returned.
 */
bool Matrix4x4_is_equal(Matrix4x4 m1, Matrix4x4 m2, double epsilon);

/**
 * Test equality against the identity matrix.
 */
bool Matrix4x4_is_identity(Matrix4x4 m, double epsilon);

/**
 * Compute the inverse of ``m``, store the result in ``out``.
 */
//TODO: Not yet implemented
//void Matrix4x4_inverse(Matrix4x4 out, const Matrix4x4 m);

#endif
