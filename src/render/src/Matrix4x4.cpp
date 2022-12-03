#include "Matrix4x4.h"

const Matrix4x4 Matrix4x4::Identity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(const Matrix4x4 & m)
{
	for (unsigned int i = 0; i < 16; i++)
		(*this)[i] = m[i];
}

Matrix4x4::Matrix4x4(float _00, float _01, float _02, float _03, float _10,
		float _11, float _12, float _13, float _20, float _21, float _22,
		float _23, float _30, float _31, float _32, float _33)
{
	this->_00 = _00, this->_01 = _01, this->_02 = _02, this->_03 = _03;
	this->_10 = _10, this->_11 = _11, this->_12 = _12, this->_13 = _13;
	this->_20 = _20, this->_21 = _21, this->_22 = _22, this->_23 = _23;
	this->_30 = _30, this->_31 = _31, this->_32 = _32, this->_33 = _33;
}

float Matrix4x4::operator ()(const unsigned int row,
		const unsigned int col) const
{
	const float* data = &_00;
	return data[row * 4 + col];
}

float & Matrix4x4::operator ()(const unsigned int row, const unsigned int col)
{
	float* data = &_00;
	return data[row * 4 + col];
}

Matrix4x4 Matrix4x4::operator -() const
{
	Matrix4x4 result;
	for (unsigned int i = 0; i < 16; i++)
		result[i] = -(*this)[i];

	return result;
}

float Matrix4x4::operator [](const unsigned int idx) const
{
	return (&_00)[idx];
}

float & Matrix4x4::operator [](const unsigned int idx)
{
	return (&_00)[idx];
}

Matrix4x4 Matrix4x4::operator +(const Matrix4x4 & m) const
{
	Matrix4x4 result;
	for (unsigned int i = 0; i < 16; i++)
		result[i] = (*this)[i] + m[i];

	return result;
}

Matrix4x4 & Matrix4x4::operator +=(const Matrix4x4 & m)
{
	*this = *this + m;
	return *this;
}

Matrix4x4 Matrix4x4::operator -(const Matrix4x4 & m) const
{
	Matrix4x4 result;
	for (unsigned int i = 0; i < 16; i++)
		result[i] = (*this)[i] - m[i];

	return result;
}

Matrix4x4 & Matrix4x4::operator -=(const Matrix4x4 & m)
{
	*this = *this - m;
	return *this;
}

Matrix4x4 Matrix4x4::operator *(const float s) const
{
	Matrix4x4 result;
	for (unsigned int i = 0; i < 16; i++)
		result[i] = (*this)[i] * s;

	return result;
}

Vec3 Matrix4x4::operator *(const Vec3 & v) const
{
	Vec3 result;
	result.x = _00 * v.x + _01 * v.y + _02 * v.z + _03;
	result.y = _10 * v.x + _11 * v.y + _12 * v.z + _13;
	result.z = _20 * v.x + _21 * v.y + _22 * v.z + _23;

	return result;
}

Matrix4x4 Matrix4x4::operator *(const Matrix4x4 & m) const
{
	Matrix4x4 result;
	for (unsigned int y = 0; y < 4; y++)
	{
		for (unsigned int x = 0; x < 4; x++)
		{
			result(y, x) = 0.0f;
			for (unsigned int k = 0; k < 4; k++)
				result(y, x) += (*this)(y, k) * m(k, x);
		}
	}

	return result;
}

Vec3 Matrix4x4::TransformDirection(const Vec3& v) const
{
	Vec3 result;
	result.x = _00 * v.x + _01 * v.y + _02 * v.z;
	result.y = _10 * v.x + _11 * v.y + _12 * v.z;
	result.z = _20 * v.x + _21 * v.y + _22 * v.z;

	return result;
}

Matrix4x4 Matrix4x4::Product(const Matrix4x4 & m) const
{
	Matrix4x4 result;
	for (unsigned int i = 0; i < 16; i++)
		result[i] = (*this)[i] * m[i];

	return result;
}

Matrix4x4 Matrix4x4::Transposed() const
{
	Matrix4x4 result;
	for (unsigned int y = 0; y < 4; y++)
	{
		for (unsigned int x = 0; x < 4; x++)
		{
			result(y, x) = (*this)(x, y);
		}
	}

	return result;
}

Matrix4x4 & Matrix4x4::Transpose()
{
	for (unsigned int y = 0; y < 3; y++)
	{
		for (unsigned int x = y + 1; x < 4; x++)
		{
			float tmp = (*this)(y, x);
			(*this)(y, x) = (*this)(x, y);
			(*this)(x, y) = tmp;
		}
	}

	return *this;
}

Matrix4x4 Matrix4x4::RotationX(const float angle)
{
	Matrix4x4 result(Identity);
	result._11 = cosf(angle), result._12 = -sinf(angle);
	result._21 = sinf(angle), result._22 = cosf(angle);

	return result;
}

Matrix4x4 Matrix4x4::RotationY(const float angle)
{
	Matrix4x4 result(Identity);
	result._00 = cosf(angle), result._02 = sinf(angle);
	result._20 = -sinf(angle), result._22 = cosf(angle);

	return result;
}

Matrix4x4 Matrix4x4::RotationZ(const float angle)
{
	Matrix4x4 result(Identity);
	result._00 = cosf(angle), result._01 = -sinf(angle);
	result._10 = sinf(angle), result._11 = cosf(angle);

	return result;
}

Matrix4x4 Matrix4x4::Rotation(const Vec3 & axis, const float angle)
{
	Matrix4x4 result(Identity);

	result._00 = cosf(angle) + axis.x * axis.x * (1.0f - cosf(angle));
	result._01 = axis.x * axis.y * (1.0f - cosf(angle)) - axis.z * sinf(angle);
	result._02 = axis.x * axis.z * (1.0f - cosf(angle)) - axis.y * sinf(angle);

	result._10 = axis.y * axis.x * (1.0f - cosf(angle)) - axis.z * sinf(angle);
	result._11 = cosf(angle) + axis.y * axis.y * (1.0f - cosf(angle));
	result._12 = axis.y * axis.z * (1.0f - cosf(angle)) - axis.x * sinf(angle);

	result._20 = axis.z * axis.x * (1.0f - cosf(angle)) - axis.y * sinf(angle);
	result._21 = axis.z * axis.y * (1.0f - cosf(angle)) - axis.x * sinf(angle);
	result._22 = cosf(angle) + axis.z * axis.z * (1.0f - cosf(angle));

	return result;
}

Matrix4x4 Matrix4x4::Scaling(const float scale)
{
	Matrix4x4 result(Identity);
	result._00 = scale;
	result._11 = scale;
	result._22 = scale;

	return result;
}

Matrix4x4 Matrix4x4::Scaling(const float sx, const float sy, const float sz)
{
	Matrix4x4 result(Identity);
	result._00 = sx;
	result._11 = sy;
	result._22 = sz;

	return result;
}

Matrix4x4 Matrix4x4::Scaling(const Vec3 & scale)
{
	Matrix4x4 result(Identity);
	result._00 = scale.x;
	result._11 = scale.y;
	result._22 = scale.z;

	return result;
}

Matrix4x4 Matrix4x4::Translation(const float tx, const float ty, const float tz)
{
	Matrix4x4 result(Identity);
	result._03 = tx;
	result._13 = ty;
	result._23 = tz;

	return result;
}

Matrix4x4 Matrix4x4::Translation(const Vec3 translation)
{
	Matrix4x4 result(Identity);
	result._03 = translation.x;
	result._13 = translation.y;
	result._23 = translation.z;

	return result;
}

Matrix4x4 Matrix4x4::ShearingXtoY(const float factor)
{
	Matrix4x4 result(Identity);
	result._10 = factor;

	return result;
}

Matrix4x4 Matrix4x4::ShearingXtoZ(const float factor)
{
	Matrix4x4 result(Identity);
	result._20 = factor;

	return result;
}

Matrix4x4 Matrix4x4::ShearingYtoX(const float factor)
{
	Matrix4x4 result(Identity);
	result._01 = factor;

	return result;
}

Matrix4x4 Matrix4x4::ShearingYtoZ(const float factor)
{
	Matrix4x4 result(Identity);
	result._21 = factor;

	return result;
}

Matrix4x4 Matrix4x4::ShearingZtoX(const float factor)
{
	Matrix4x4 result(Identity);
	result._02 = factor;

	return result;
}

Matrix4x4 Matrix4x4::ShearingZtoY(const float factor)
{
	Matrix4x4 result(Identity);
	result._12 = factor;

	return result;
}

Matrix4x4 Matrix4x4::ViewMatrix(const Vec3 &eye, const Vec3 &direction,
		const Vec3 &worldUp)
{
	Matrix4x4 viewMatrix(Matrix4x4::Identity);

	Vec3 right = Vec3::cross(direction, worldUp);
	right.normalize();
	Vec3 up = Vec3::cross(right, direction);
	up.normalize();

	viewMatrix._00 = right.x, viewMatrix._01 = right.y, viewMatrix._02 = right.z;
	viewMatrix._10 = direction.x, viewMatrix._11 = direction.y, viewMatrix._12 =
			direction.z;
	viewMatrix._20 = up.x, viewMatrix._21 = up.y, viewMatrix._22 = up.z;
	viewMatrix = viewMatrix * Matrix4x4::Translation(-eye);

	return viewMatrix;
}
