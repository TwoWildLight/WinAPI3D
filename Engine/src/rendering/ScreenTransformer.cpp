#include "ScreenTransformer.h"
#include "../core/Graphics.h"

void ScreenTransformer::Transform(const Graphics& gfx, PNVertex& v)
{
	const float xFactor = gfx.GetWidth() / 2.0f;
	const float yFactor = gfx.GetHeight() / 2.0f;

	v.pos *= 1.0f / abs(v.pos.z);
	v.pos.x = v.pos.x * xFactor + xFactor;
	v.pos.y = -v.pos.y * yFactor + yFactor;
}