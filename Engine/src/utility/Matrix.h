#pragma once

class Vector3;

class Matrix
{
public:
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float cells[4][4];
	};

public:
	Matrix() = default;

public:
	static Matrix Identity();

	static Matrix Transpose(const Matrix& m);

	static Matrix Scaling(const Vector3& v);
	static Matrix Scaling(float x, float y, float z);

	static Matrix Rotation(const Vector3& v);
	static Matrix Rotation(float x, float y, float z);
	static Matrix RotationX(float ang);
	static Matrix RotationY(float ang);
	static Matrix RotationZ(float ang);

	static Matrix Translation(const Vector3& v);
	static Matrix Translation(float x, float y, float z);

	Matrix operator *(const Matrix& rhs) const;
	Matrix& operator *=(const Matrix& rhs);
};