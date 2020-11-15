#include "ScreenTransformer.h"
#include "../core/Graphics.h"

void ScreenTransformer::Transform(const Graphics& gfx, DVTX::Vertex v)
{
	using Type = DVTX::VertexLayout::Element::Type;

	auto& pos = v.Attr<Vector3>(Type::POSITION3D);

	const float xFactor = gfx.GetWidth() / 2.0f;
	const float yFactor = gfx.GetHeight() / 2.0f;

	pos *= 1.0f / abs(pos.z);
	pos.x = pos.x * xFactor + xFactor;
	pos.y = -pos.y * yFactor + yFactor;
}