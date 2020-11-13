#pragma once

class Vector2
{
public:
	float x, y;

public:
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}

public:

};

class Vector3 : public Vector2
{
public:
	float z;

public:
	Vector3() : Vector2(), z(0.0f) {}
	Vector3(float x, float y, float z) : Vector2(x,y), z(z) {}

public:

};