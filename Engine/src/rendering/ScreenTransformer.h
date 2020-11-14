#pragma once
#include "../core/Graphics.h"
#include "DynamicVertex.h"

class ScreenTransformer
{
public:
	void Transform(const Graphics& gfx, DVTX::Vertex v)
	{
		using Type = DVTX::VertexLayout::Element::Type;
		
		auto& pos = v.Attr<Vector3>(Type::POSITION3D);
		auto& sv_pos = v.Attr<Vector4>(Type::POSITION4D);

		const float xFactor = gfx.GetWidth() / 2.0f;
		const float yFactor = gfx.GetHeight() / 2.0f;

		pos *= 1.0f / sv_pos.w;
		pos.x = pos.x * xFactor + xFactor;
		pos.y = -pos.y * yFactor + yFactor;
	}
};