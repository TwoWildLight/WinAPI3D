#include "Rasterizer.h"
#include "PixelShader.h"
#include "OutputMerger.h"

void Rasterizer::DrawLine(PixelShader& ps, OutputMerger& om, DVTX::Vertex from, DVTX::Vertex to)
{
	using VertexType = DVTX::VertexLayout::Element::Type;
	const auto& vFrom = from.Attr<Vector3>(VertexType::POSITION3D);
	const auto& vTo = to.Attr<Vector3>(VertexType::POSITION3D);

	float sx = vFrom.x, sy = vFrom.y;
	float dx = vTo.x, dy = vTo.y;

	float slopeM = 0.0f;
	float offsetB;

	slopeM = (dy - sy) / (dx - sx);
	offsetB = sy - sx * slopeM;

	if ((slopeM <= 1.0 && slopeM >= -1.0f && slopeM != 0.0f) || sy == dy)
	{
		int xFrom = (int)std::min(sx, dx);
		int xTo = (int)std::max(sx, dx);
		int length = xTo - xFrom;

		for (; xFrom < xTo; xFrom++)
		{
			if ((xTo - xFrom) / (float)length * vTo.z < 0.0f) continue;
			float y = slopeM * xFrom + offsetB;
			om.PutPixel(xFrom, (int)y, ps(from));
		}
	}
	else {
		int yFrom = (int)std::min(sy, dy);
		int yTo = (int)std::max(sy, dy);
		int length = yTo - yFrom;

		for (; yFrom < yTo; yFrom++)
		{
			if ((yTo - yFrom) / (float)length * vTo.z < 0.0f) continue;
			float x = yFrom / slopeM - offsetB / slopeM;
			if (sx == dx) x = sx;
			om.PutPixel((int)x, yFrom, ps(to));
		}
	}
}
