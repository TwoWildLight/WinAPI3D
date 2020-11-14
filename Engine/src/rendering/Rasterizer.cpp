#include "Rasterizer.h"

Rasterizer::Rasterizer(Graphics& gfx)
	:
	gfx(gfx)
{}

void Rasterizer::DrawLine(const Vector3& from, const Vector3& to, const Vector3& c)
{
	float slopeM = 0.0f;
	float offsetB;

	slopeM = (to.y - from.y) / (to.x - from.x);
	offsetB = from.y - from.x * slopeM;

	if ((slopeM <= 1.0 && slopeM >= -1.0f && slopeM != 0.0f) || from.y == to.y)
	{
#pragma warning (disable : 4244)
		int xFrom = std::min(from.x, to.x);
		int xTo = std::max(from.x, to.x);
		float length = (float)xTo - (float)xFrom;

		for (; xFrom < xTo; xFrom++)
		{
			if((xTo - xFrom) / length * to.z < 0.0f) continue;
			float y = slopeM * xFrom + offsetB;
			gfx.PutPixel(xFrom, (int)y, c);
		}
	}
	else {
		int yFrom = std::min(from.y, to.y);
		int yTo = std::max(from.y, to.y);
		float length = (float)yTo - (float)yFrom;

		for (; yFrom < yTo; yFrom++)
		{
			if ((yTo - yFrom) / length * to.z < 0.0f) continue;
			float x = yFrom / slopeM - offsetB / slopeM;
			if (from.x == to.x) x = from.x;
			gfx.PutPixel((int)x, yFrom, c);
		}
	}
}
