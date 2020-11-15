#include "Rasterizer.h"
#include "PixelShader.h"
#include "OutputMerger.h"

void Rasterizer::DrawLine(PixelShader& ps, OutputMerger& om, PNVertex& from, PNVertex& to)
{
	float sx = from.sv_pos.x, sy = from.sv_pos.y;
	float dx = to.sv_pos.x, dy = to.sv_pos.y;

	float slopeM = (dy - sy) / (dx - sx);
	float offsetB = sy - sx * slopeM;

	if ((slopeM <= 1.0 && slopeM >= -1.0f && slopeM != 0.0f) || sy == dy)
	{
		int xFrom = (int)std::min(sx, dx);
		int xTo = (int)std::max(sx, dx);
		int length = xTo - xFrom;

		for (; xFrom < xTo; xFrom++)
		{
			if ((xTo - xFrom) / (float)length * to.sv_pos.z < 0.0f) continue;
			float y = slopeM * xFrom + offsetB;
			om.PutPixel(xFrom, (int)y, 0.0f, ps(from));
		}
	}
	else {
		int yFrom = (int)std::min(sy, dy);
		int yTo = (int)std::max(sy, dy);
		int length = yTo - yFrom;

		for (; yFrom < yTo; yFrom++)
		{
			if ((yTo - yFrom) / (float)length * to.sv_pos.z < 0.0f) continue;
			float x = yFrom / slopeM - offsetB / slopeM;
			if (sx == dx) x = sx;
			om.PutPixel((int)x, yFrom, 0.0f, ps(to));
		}
	}
}

void Rasterizer::DrawTriangle(PixelShader& ps, OutputMerger& om, Triangle<PNVertex> t)
{
	if (Vector3::Dot(Vector3(0.0f, 0.0f, 1.0f), Vector3::Cross(t.v1.sv_pos - t.v0.sv_pos, t.v2.sv_pos - t.v0.sv_pos)) > 0.0f)
	{
		DrawTriangle(ps, om, t.v0, t.v1, t.v2);
	}
}

void Rasterizer::DrawTriangle(PixelShader& ps, OutputMerger& om, PNVertex& v0, PNVertex& v1, PNVertex& v2)
{
	if (v0.sv_pos.y > v1.sv_pos.y) std::swap(v0, v1);
	if (v0.sv_pos.y > v2.sv_pos.y) std::swap(v0, v2);
	if (v1.sv_pos.y > v2.sv_pos.y) std::swap(v1, v2);

	PNVertex vTopMiddle = v1 - v0;
	PNVertex vTopBottom = v2 - v0;
	float yRatio = (v1.sv_pos.y - v0.sv_pos.y) / (v2.sv_pos.y - v0.sv_pos.y);
	PNVertex split = vTopBottom * yRatio + v0;

	if (split.sv_pos.x > v1.sv_pos.x) std::swap(split, v1);
	DrawFlatTopTriangle(ps, om, split, v1, v2);
	DrawFlatBottomTriangle(ps, om, v1, split, v0);
}

void Rasterizer::DrawFlatTopTriangle(PixelShader& ps, OutputMerger& om, PNVertex& left, PNVertex& right, PNVertex& bottom)
{
	int yFrom = (int)left.sv_pos.y;
	int yTo = (int)bottom.sv_pos.y;

	auto vLeftBottom = bottom - left;
	auto vRightBottom = bottom - right;

	for (int y = yFrom; y < yTo; y++)
	{
		float yRatio = (float)(y - yFrom) / (yTo - yFrom);
		auto iLeft = vLeftBottom * yRatio + left;
		auto iRight = vRightBottom * yRatio + right;

		DrawScanLine(ps, om, iLeft, iRight, y);
	}
}

void Rasterizer::DrawFlatBottomTriangle(PixelShader& ps, OutputMerger& om, PNVertex& right, PNVertex& left, PNVertex& top)
{
	int yFrom = (int)top.sv_pos.y;
	int yTo = (int)right.sv_pos.y;

	PNVertex vTopLeft = left - top;
	PNVertex vTopRight = right - top;

	for (int y = yFrom; y < yTo; y++)
	{
		float yRatio = (float)(y - yFrom) / (yTo - yFrom);
		PNVertex iLeft = vTopLeft * yRatio + top;
		PNVertex iRight = vTopRight * yRatio + top;

		DrawScanLine(ps, om, iLeft, iRight, y);
	}
}

void Rasterizer::DrawScanLine(PixelShader& ps, OutputMerger& om, PNVertex& iLeft, PNVertex& iRight, int y)
{
	int xFrom = (int)floorf(iLeft.sv_pos.x + 0.5f);
	int xTo = (int)ceilf(iRight.sv_pos.x + 0.5f);

	auto step = (iRight - iLeft) / (float)(xTo - xFrom);

	for (; xFrom < xTo; xFrom++, iLeft += step)
	{
		auto vertex = iLeft;
		om.PutPixel(xFrom, y, vertex.pos.z, ps(vertex));
	}
}