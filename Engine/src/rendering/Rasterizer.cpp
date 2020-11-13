#include "Rasterizer.h"

Rasterizer::Rasterizer(Graphics& gfx)
	:
	gfx(gfx)
{}

void Rasterizer::DrawLine(const Vector2& from, const Vector2& to, const Vector3& c)
{
	DrawLine(from.x, from.y, to.x, to.y, c);
}

void Rasterizer::DrawLine(float sx, float sy, float dx, float dy, const Vector3& c)
{
	float slopeM = 0.0f;
	float offsetB;

	slopeM = (dy - sy) / (dx - sx);
	offsetB = sy - sx * slopeM;

	if ((slopeM <= 1.0 && slopeM >= -1.0f && slopeM != 0.0f) || sy == dy)
	{
#pragma warning (disable : 4244)
		int xFrom = std::min(sx, dx);
		int xTo = std::max(sx, dx);

		for (; xFrom < xTo; xFrom++)
		{
			float y = slopeM * xFrom + offsetB;
			gfx.PutPixel(xFrom, (int)y, c);
		}
	}
	else {
		int yFrom = std::min(sy, dy);
		int yTo = std::max(sy, dy);

		for (; yFrom < yTo; yFrom++)
		{
			float x = yFrom / slopeM - offsetB / slopeM;
			if (sx == dx) x = sx;
			gfx.PutPixel((int)x, yFrom, c);
		}
	}
}
