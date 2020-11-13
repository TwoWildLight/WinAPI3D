#include "Matrix.h"	
#include "Vector.h"
#include <utility>

Matrix Matrix::Identity()
{
	Matrix m;
	m._11 = 1.0f, m._12 = 0.0f, m._13 = 0.0f, m._14 = 0.0f;
	m._21 = 0.0f, m._22 = 1.0f, m._23 = 0.0f, m._24 = 0.0f;
	m._31 = 0.0f, m._32 = 0.0f, m._33 = 1.0f, m._34 = 0.0f;
	m._41 = 0.0f, m._42 = 0.0f, m._43 = 0.0f, m._44 = 1.0f;
	return std::move(m);
}

Matrix Matrix::Transpose(const Matrix& m)
{
	Matrix res = m;
	std::swap(res._12, res._21);
	std::swap(res._13, res._31);
	std::swap(res._14, res._41);
	std::swap(res._23, res._32);
	std::swap(res._24, res._42);
	std::swap(res._34, res._43);
	return std::move(res);
}

Matrix Matrix::Scaling(const Vector3& v)
{
	return Scaling(v.x, v.y, v.z);
}

Matrix Matrix::Scaling(float x, float y, float z)
{
	Matrix m;
	m._11 = x;
	m._22 = y;
	m._33 = z;
	return std::move(m);
}

Matrix Matrix::Rotation(const Vector3& v)
{
	return Rotation(v.x, v.y, v.z);
}

Matrix Matrix::Rotation(float x, float y, float z)
{
	return RotationZ(z) * RotationX(x) * RotationY(y);
}

Matrix Matrix::RotationX(float ang)
{
	Matrix m = Identity();
	float cosTheta = cosf(ang);
	float sinTheta = sinf(ang);
	m._22 = cosTheta; m._23 = sinTheta;
	m._32 = -sinTheta; m._33 = cosTheta;
	return std::move(m);
}

Matrix Matrix::RotationY(float ang)
{
	Matrix m = Identity();
	float cosTheta = cosf(ang);
	float sinTheta = sinf(ang);
	m._11 = cosTheta; m._13 = -sinTheta;
	m._31 = sinTheta; m._33 = cosTheta;
	return std::move(m);
}

Matrix Matrix::RotationZ(float ang)
{
	Matrix m = Identity();
	float cosTheta = cosf(ang);
	float sinTheta = sinf(ang);
	m._11 = cosTheta; m._12 = sinTheta;
	m._21 = -sinTheta; m._22 = cosTheta;
	return std::move(m);
}

Matrix Matrix::Translation(const Vector3& v)
{
	return Translation(v.x, v.y, v.z);
}

Matrix Matrix::Translation(float x, float y, float z)
{
	Matrix m = Identity();
	m._41 = x;
	m._42 = y;
	m._43 = z;
	return std::move(m);
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	Matrix m;
	for (int row_left = 0; row_left < 4; row_left++)
		for (int col_right = 0; col_right < 4; col_right++)
		{
			m.cells[row_left][col_right] = 0;
			for (int i = 0; i < 4; i++)
				m.cells[row_left][col_right] += cells[row_left][i] * rhs.cells[i][col_right];
		}
	return std::move(m);
}

Matrix& Matrix::operator*=(const Matrix& rhs)
{
	return *this = *this * rhs;
}
