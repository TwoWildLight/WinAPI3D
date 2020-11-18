#include "NDCScreenTransformer.h"
#include "../core/Graphics.h"

void NDCScreenTransformer::Transform(const Graphics& gfx, Vertex& v)
{
	const float xFactor = gfx.GetWidth() / 2.0f;
	const float yFactor = gfx.GetHeight() / 2.0f;

	float winv = 1.0f / v.sv_pos.w;
	v.sv_pos *= winv;
	v.tc *= winv;
	v.sv_pos.w = winv;

	v.sv_pos.x = v.sv_pos.x * xFactor + xFactor;
	v.sv_pos.y = -v.sv_pos.y * yFactor + yFactor;
}

void NDCScreenTransformer::Transform(const Graphics& gfx, Triangle<Vertex>& t)
{
	Transform(gfx, t.v0);
	Transform(gfx, t.v1);
	Transform(gfx, t.v2);
}