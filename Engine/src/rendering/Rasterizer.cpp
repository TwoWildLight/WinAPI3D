#include "Rasterizer.h"

void Rasterizer::DrawLine(Graphics& gfx, const DVTX::Vertex& from, const DVTX::Vertex& to)
{
	using Type = DVTX::VertexLayout::Element::Type;

	float slopeM = 0.0f;
	float offsetB;

	slopeM = (to.Attr<Vector3>(Type::POSITION3D).y - from.Attr<Vector3>(Type::POSITION3D).y) / (to.Attr<Vector3>(Type::POSITION3D).x - from.Attr<Vector3>(Type::POSITION3D).x);
	offsetB = from.Attr<Vector3>(Type::POSITION3D).y - from.Attr<Vector3>(Type::POSITION3D).x * slopeM;

	if ((slopeM <= 1.0 && slopeM >= -1.0f && slopeM != 0.0f) || from.Attr<Vector3>(Type::POSITION3D).y == to.Attr<Vector3>(Type::POSITION3D).y)
	{
#pragma warning (disable : 4244)
		int xFrom = std::min(from.Attr<Vector3>(Type::POSITION3D).x, to.Attr<Vector3>(Type::POSITION3D).x);
		int xTo = std::max(from.Attr<Vector3>(Type::POSITION3D).x, to.Attr<Vector3>(Type::POSITION3D).x);
		float length = (float)xTo - (float)xFrom;

		for (; xFrom < xTo; xFrom++)
		{
			if((xTo - xFrom) / length * to.Attr<Vector3>(Type::POSITION3D).z < 0.0f) continue;
			float y = slopeM * xFrom + offsetB;
			gfx.PutPixel(xFrom, (int)y, defaultColor);
		}
	}
	else {
		int yFrom = std::min(from.Attr<Vector3>(Type::POSITION3D).y, to.Attr<Vector3>(Type::POSITION3D).y);
		int yTo = std::max(from.Attr<Vector3>(Type::POSITION3D).y, to.Attr<Vector3>(Type::POSITION3D).y);
		float length = (float)yTo - (float)yFrom;

		for (; yFrom < yTo; yFrom++)
		{
			if ((yTo - yFrom) / length * to.Attr<Vector3>(Type::POSITION3D).z < 0.0f) continue;
			float x = yFrom / slopeM - offsetB / slopeM;
			if (from.Attr<Vector3>(Type::POSITION3D).x == to.Attr<Vector3>(Type::POSITION3D).x) x = from.Attr<Vector3>(Type::POSITION3D).x;
			gfx.PutPixel((int)x, yFrom, defaultColor);
		}
	}
}
