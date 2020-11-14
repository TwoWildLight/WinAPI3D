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

Matrix Matrix::LookAt(const Vector3& pos, const Vector3& dir, const Vector3& up)
{
	const Vector3 right = Vector3::Cross(up, dir);
	Matrix m = Identity();
	m._11 = right.x, m._12 = up.x, m._13 = dir.x;
	m._21 = right.y, m._22 = up.y, m._23 = dir.y;
	m._31 = right.z, m._32 = up.z, m._33 = dir.z;
	m._41 = -Vector3::Dot(pos, right), m._42 = -Vector3::Dot(pos, up), m._43 = -Vector3::Dot(pos, dir);
	return std::move(m);
}

Matrix Matrix::Projection(float fov, float aspectRatio, float near, float far)
{
	float w = 1.0f / tanf(fov * 0.5f);
	float h = w * aspectRatio;
	float Q = far / (far - near);

	Matrix m = Identity();
	m._11 = w;
	m._22 = h;
	m._33 = Q;
	m._34 = 1.0f;
	m._43 = -Q * near;
	m._44 = 0.0f;

	return std::move(m);
}

Vector3 Matrix::ToEuler(const Matrix& m)
{
	float pitch, yaw, roll;
	static constexpr float PI_F = 3.141592F;

	// https://www.geometrictools.com/Documentation/EulerAngles.pdf
	if (m._23 < 1.0f)
	{
		if (m._23 > -1.0f)
		{
			pitch = (float)asin(-m._23);
			yaw = (float)atan2(m._13, m._33);
			roll = (float)atan2(m._21, m._22);
		}
		else // r12 = -1, not a unique solution roll + yaw = atan(-r01, r00) 
		{
			pitch = PI_F / 2.0f;
			yaw = (float)-atan2(-m._12, m._11);
			roll = 0.0f;
		}
	}
	else // not a unique solution roll - yaw = atan(-r01, r00) 
	{
		pitch = -PI_F / 2.0f;
		yaw = (float)atan2(-m._12, m._11);
		roll = 0.0f;
	}
	return { pitch, yaw, roll };
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
