#include "ScreenTransformer.h"
#include "../core/Graphics.h"

void ScreenTransformer::Transform(const Graphics& gfx, Vertex& v)
{
	const float xFactor = gfx.GetWidth() / 2.0f;
	const float yFactor = gfx.GetHeight() / 2.0f;

	float invZ = 1.0f / abs(v.sv_pos.z);
	v.sv_pos *= invZ;
	v.sv_pos.z = invZ;
	v.tc *= invZ;

	v.sv_pos.x = v.sv_pos.x * xFactor + xFactor;
	v.sv_pos.y = -v.sv_pos.y * yFactor + yFactor;
}

void ScreenTransformer::Transform(const Graphics& gfx, Triangle<Vertex>& t)
{
	Transform(gfx, t.v0);
	Transform(gfx, t.v1);
	Transform(gfx, t.v2);
}