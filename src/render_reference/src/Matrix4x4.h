#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vec3.h"

struct Matrix4x4
{
	float _00, _01, _02, _03;
	float _10, _11, _12, _13;
	float _20, _21, _22, _23;
	float _30, _31, _32, _33;

	static const Matrix4x4 Identity;

	/**
	 * Empty constructor doing nothing.
	 */
	Matrix4x4();
	/**
	 * Clone constructor. Initializes the matrix from another matrix.
	 * @ m Other matrix to clone.
	 */
	Matrix4x4(const Matrix4x4& m);
	/**
	 * Init constructor. Initializes the matrix from scalar values.
	 */
	Matrix4x4(float _00, float _01, float _02, float _03, float _10, float _11,
			float _12, float _13, float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33);

	/**
	 * Allows readonly access to the matrix components by using ::Matrix4x4(row, col).
	 * @param row Row of the matrix to address.
	 * @param col Column of the matrix to address.
	 * @returns Value on that position.
	 */
	float operator()(const unsigned int row, const unsigned int col) const;
	/**
	 * Allows access to the matrix components by using ::Matrix4x4(row, col).
	 * @param row Row of the matrix to address.
	 * @param col Column of the matrix to address.
	 * @returns Value on that position.
	 */
	float& operator()(const unsigned int row, const unsigned int col);

	/**
	 * Allows readonly access to the matrix components a row major order index.
	 * @param idx Row major order index.
	 * @returns Value on that position.
	 */
	float operator[](const unsigned int idx) const;
	/**
	 * Allows access to the matrix components by using a row major order index.
	 * @param idx Row major order index.
	 * @returns Value on that position.
	 */
	float& operator[](const unsigned int idx);

	/**
	 * Returns the componentwise negated matrix.
	 * @returns Negated matrix.
	 */
	Matrix4x4 operator-() const;
	/**
	 * Adds two matrices componentwise.
	 * @param m Other matrix to add.
	 * @returns Componentwise sum of the current matrix and m.
	 */
	Matrix4x4 operator+(const Matrix4x4 &m) const;
	/**
	 * Adds another matrix to the current matrix componentwise.
	 * @param m Other matrix to add.
	 * @returns Reference to the current matrix after adding m.
	 */
	Matrix4x4& operator+=(const Matrix4x4 &m);
	/**
	 * Calculates the componentwise difference between the current matrix and m.
	 * @param m Matrix to subtract.
	 * @returns Current matrix minus m.
	 */
	Matrix4x4 operator -(const Matrix4x4 &m) const;
	/**
	 * Subtracts another matrix componentwise from the current matrix.
	 * @param m Other matrix to subtract.
	 * @returns Reference to the current matrix after subtracting m.
	 */
	Matrix4x4& operator -=(const Matrix4x4 &m);

	/**
	 * Multiplies all matrix values by a certain factor.
	 * @param s Scalar multiplication factor
	 * @returns multiplied matrix.
	 */
	Matrix4x4 operator*(const float s) const;
	/**
	 * Transforms an homogeneous point.
	 * @param v 3D vector treated as 4D homogeneous point.
	 * @returns First three components of the transformed point.
	 */
	Vec3 operator*(const Vec3& v) const;
	/**
	 * Matrix multiplication.
	 * @param m Other matrix to multiply.
	 * @returns Result of the matrix multiplication.
	 */
	Matrix4x4 operator*(const Matrix4x4& m) const;
	/**
	 * Multiplies two matrices componentwise.
	 * @param m Second matrix which is multiplied componentwise.
	 * @returns Result of the componentwise matrix multiplication.
	 */
	Matrix4x4 Product(const Matrix4x4& m) const;

	/**
	 * Interpretes a 3D vector as direction and transforms it with the upper
	 * left 3x3 part of the matrix.
	 * @param v Direction vector which is to be transformed.
	 * @returns Transformed direction.
	 */
	Vec3 TransformDirection(const Vec3& v) const;

	/**
	 * Returns the transpose of the matrix.
	 */
	Matrix4x4 Transposed() const;
	/**
	 * Transposes the matrix.
	 */
	Matrix4x4& Transpose();

	/**
	 * Generates a matrix that rotates around the X axis.
	 * @param angle Rotation angle.
	 * @returns Rotation matrix.
	 */
	static Matrix4x4 RotationX(const float angle);
	/**
	 * Generates a matrix that rotates around the Y axis.
	 * @param angle Rotation angle.
	 * @returns Rotation matrix.
	 */
	static Matrix4x4 RotationY(const float angle);
	/**
	 * Generates a matrix that rotates around the Z axis.
	 * @param angle Rotation angle.
	 * @returns Rotation matrix.
	 */
	static Matrix4x4 RotationZ(const float angle);
	/**
	 * Generates a rotation matrix that rotates around an arbitrary axis.
	 * @param axis Rotation axis.
	 * @param angle Rotation angle.
	 * @returns Rotation matrix.
	 */
	static Matrix4x4 Rotation(const Vec3& axis, const float angle);

	/**
	 * Generates a uniform scaling matrix.
	 * @param scale Scaling factor.
	 * @returns Scaling matrix.
	 */
	static Matrix4x4 Scaling(const float scale);
	/**
	 * Generates a nonuniform scaling matrix.
	 * @param sx Scaling in x direction.
	 * @param sy Scaling in y direction.
	 * @param sz Scaling in z direction.
	 * @returns Scaling matrix.
	 */
	static Matrix4x4 Scaling(const float sx, const float sy, const float sz);
	/**
	 * Generates a nonuniform scaling matrix.
	 * @param scale Vector components scale along the corresponding axes.
	 * @returns Scaling matrix.
	 */
	static Matrix4x4 Scaling(const Vec3& scale);

	/**
	 * Creates a translation matrix.
	 * @param tx Translation in x direction.
	 * @param ty Translation in y direction.
	 * @param tz Translation in z direction.
	 */
	static Matrix4x4 Translation(const float tx, const float ty,
			const float tz);
	/**
	 * Creates a translation matrix.
	 * @param translation Each component contains the translation
	 * along the corresponding axis.
	 */
	static Matrix4x4 Translation(const Vec3 translation);

	/**
	 * Creates a sharing matrix that increases Y dependent on X.
	 * @param factor Shearing factor.
	 * @returns Shearing matrix.
	 */
	static Matrix4x4 ShearingXtoY(const float factor);
	/**
	 * Creates a sharing matrix that increases Z dependent on X.
	 * @param factor Shearing factor.
	 * @returns Shearing matrix.
	 */
	static Matrix4x4 ShearingXtoZ(const float factor);
	/**
	 * Creates a sharing matrix that increases X dependent on Y.
	 * @param factor Shearing factor.
	 * @returns Shearing matrix.
	 */
	static Matrix4x4 ShearingYtoX(const float factor);
	/**
	 * Creates a sharing matrix that increases Z dependent on Y.
	 * @param factor Shearing factor.
	 * @returns Shearing matrix.
	 */
	static Matrix4x4 ShearingYtoZ(const float factor);
	/**
	 * Creates a sharing matrix that increases X dependent on Z.
	 * @param factor Shearing factor.
	 * @returns Shearing matrix.
	 */
	static Matrix4x4 ShearingZtoX(const float factor);
	/**
	 * Creates a sharing matrix that increases Y dependent on Z.
	 * @param factor Shearing factor.
	 * @returns Shearing matrix.
	 */
	static Matrix4x4 ShearingZtoY(const float factor);

	/**
	 * Creates a view matrix.
	 * @param eye Position of the observer.
	 * @param direction Viewing direction.
	 * @param worldUp The world space up vector.
	 */
	static Matrix4x4 ViewMatrix(const Vec3 &eye, const Vec3 &direction,
			const Vec3 &worldUp);
};

#endif /* MATRIX_H_ */
