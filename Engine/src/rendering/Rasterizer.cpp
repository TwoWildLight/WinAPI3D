#include "Rasterizer.h"
#include "OutputMerger.h"

void Rasterizer::DrawLine(OutputMerger& om, const DVTX::Vertex& from, const DVTX::Vertex& to)
{
	using Type = DVTX::VertexLayout::Element::Type;
	const auto& vFrom = from.Attr<Vector3>(Type::POSITION3D);
	const auto& vTo = to.Attr<Vector3>(Type::POSITION3D);

	float ax = vFrom.x, ay = vFrom.y;
	float bx = vTo.x, by = vTo.y;

	float slopeM = 0.0f;
	float offsetB;

	slopeM = (by - ay) / (bx - ax);
	offsetB = ay - ax * slopeM;

	if ((slopeM <= 1.0 && slopeM >= -1.0f && slopeM != 0.0f) || ay == by)
	{
		int xFrom = (int)std::min(ax, bx);
		int xTo = (int)std::max(ax, bx);
		int length = xTo - xFrom;

		for (; xFrom < xTo; xFrom++)
		{
			if ((xTo - xFrom) / (float)length * vTo.z < 0.0f) continue;
			float y = slopeM * xFrom + offsetB;
			om.PutPixel(xFrom, (int)y, defaultColor);
		}
	}
	else {
		int yFrom = (int)std::min(ay, by);
		int yTo = (int)std::max(ay, by);
		int length = yTo - yFrom;

		for (; yFrom < yTo; yFrom++)
		{
			if ((yTo - yFrom) / (float)length * vTo.z < 0.0f) continue;
			float x = yFrom / slopeM - offsetB / slopeM;
			if (ax == bx) x = ax;
			om.PutPixel((int)x, yFrom, defaultColor);
		}
	}
}
