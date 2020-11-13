#pragma once

class Vector2
{
public:
	float x, y;

public:
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}

public:
	Vector2 operator +(const Vector2& rhs);
	Vector2& operator +=(const Vector2& rhs);
	Vector2 operator -(const Vector2& rhs);
	Vector2& operator -=(const Vector2& rhs);
	Vector2 operator *(const float factor);
	Vector2& operator *=(const float factor);
	Vector2 operator /(const float factor);
	Vector2& operator /=(const float factor);
};

class Vector3 : public Vector2
{
public:
	float z;

public:
	Vector3() : Vector2(), z(0.0f) {}
	Vector3(float x, float y, float z) : Vector2(x,y), z(z) {}

public:
	Vector3 operator +(const Vector3& rhs);
	Vector3& operator +=(const Vector3& rhs);
	Vector3 operator -(const Vector3& rhs);
	Vector3& operator -=(const Vector3& rhs);
	Vector3 operator *(const float factor);
	Vector3& operator *=(const float factor);
	Vector3 operator /(const float factor);
	Vector3& operator /=(const float factor);
};