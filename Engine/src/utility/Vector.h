#pragma once

static constexpr float PI_F = 3.141592F;

class Matrix;

class Vector2
{
public:
	float x, y;

public:
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}

public:
	float Length() const;
	void Normalize();
	float Dot(const Vector2& v) const;

	static Vector2 Normalize(const Vector2& v);
	static float Dot(const Vector2& lhs, const Vector2& rhs);

	Vector2 operator +(const Vector2& rhs) const;
	Vector2& operator +=(const Vector2& rhs);
	Vector2 operator -(const Vector2& rhs) const;
	Vector2& operator -=(const Vector2& rhs);
	Vector2 operator *(const float factor) const;
	Vector2& operator *=(const float factor);
	Vector2 operator /(const float factor) const;
	Vector2& operator /=(const float factor);
};

class Vector3 : public Vector2
{
public:
	float z;

public:
	Vector3() : Vector2(), z(0.0f) {}
	Vector3(float x, float y, float z) : Vector2(x,y), z(z) {}
	Vector3(const Vector2& v) : Vector2(v), z(1.0f) {}

public:
	float Length() const;
	void Normalize();
	float Dot(const Vector3& v) const;
	Vector3 Cross(const Vector3& v) const;

	static Vector3 Normalize(const Vector3& v);
	static float Dot(const Vector3& lhs, const Vector3& rhs);
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

	Vector3 operator +(const Vector3& rhs) const;
	Vector3& operator +=(const Vector3& rhs);
	Vector3 operator -(const Vector3& rhs) const;
	Vector3& operator -=(const Vector3& rhs);
	Vector3 operator *(const float factor) const;
	Vector3& operator *=(const float factor);
	Vector3 operator /(const float factor) const;
	Vector3& operator /=(const float factor);

	Vector3 operator *(const Matrix& m) const;
	Vector3& operator *=(const Matrix& m);
};

class Vector4 : public Vector3
{
public:
	float w;

public:
	Vector4() : Vector3(), w(0.0f) {}
	Vector4(float x, float y, float z, float w) : Vector3(x, y, z), w(w) {}
	Vector4(const Vector3& v) : Vector3(v), w(1.0f) {}

	Vector4 operator +(const Vector4& rhs) const;
	Vector4& operator +=(const Vector4& rhs);
	Vector4 operator -(const Vector4& rhs) const;
	Vector4& operator -=(const Vector4& rhs);
	Vector4 operator *(const float factor) const;
	Vector4& operator *=(const float factor);
	Vector4 operator /(const float factor) const;
	Vector4& operator /=(const float factor);

	Vector4 operator *(const Matrix& m) const;
	Vector4& operator *=(const Matrix& m);
};