#include "ScreenTransformer.h"
#include "../core/Graphics.h"

void ScreenTransformer::Transform(const Graphics& gfx, PNVertex& v)
{
	const float xFactor = gfx.GetWidth() / 2.0f;
	const float yFactor = gfx.GetHeight() / 2.0f;

	v.sv_pos *= 1.0f / abs(v.pos.z);
	v.sv_pos.x = v.sv_pos.x * xFactor + xFactor;
	v.sv_pos.y = -v.sv_pos.y * yFactor + yFactor;
}