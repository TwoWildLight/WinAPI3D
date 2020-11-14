#pragma once
#include "../core/Graphics.h"

class Rasterizer
{
private:
	Graphics& gfx;

public:
	Rasterizer(Graphics& gfx);

public:
	void DrawLine(const Vector3& from, const Vector3& to, const Vector3& c);
};