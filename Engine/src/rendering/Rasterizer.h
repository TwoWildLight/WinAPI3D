#pragma once
#include "../core/Graphics.h"

class Rasterizer
{
private:
	Graphics& gfx;

public:
	Rasterizer(Graphics& gfx);

public:
	void DrawLine(const Vector2& from, const Vector2& to, const Vector3& c);
	void DrawLine(float sx, float sy, float dx, float dy, const Vector3& c);
};