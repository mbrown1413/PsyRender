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
 * Copy matrix ``m`` to ``out``.
 */
void Matrix4x4_copy(Matrix4x4 out, Matrix4x4 m);

/**
 * Multiply matrices ``m1`` with ``m2``, store the result in ``out``.
 */
void Matrix4x4_multiply(Matrix4x4 out, Matrix4x4 m1, Matrix4x4 m2);

/**
 * Test equality of matrices ``m1`` and ``m2`` with tolerance ``epsilon``.
 *
 * The matrices are compared element by element. If all ``m1[i][j]`` and
 * ``m2[i][j]`` are within ``epsilon`` of eachother, ``true`` is returned.
 */
bool Matrix4x4_is_equal(Matrix4x4 m1, Matrix4x4 m2, double epsilon);

/**
 * Compute the inverse of ``m``, store the result in ``out``.
 */
//TODO: Not yet implemented
//void Matrix4x4_inverse(Matrix4x4 out, const Matrix4x4 m);

#endif
