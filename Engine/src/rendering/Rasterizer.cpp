#include "Rasterizer.h"
#include "PixelShader.h"
#include "OutputMerger.h"

void Rasterizer::DrawLine(PixelShader& ps, OutputMerger& om, Triangle<Vertex>& t)
{
	DrawLine(ps, om, t.v0, t.v1);
	DrawLine(ps, om, t.v1, t.v2);
	//DrawLine(ps, om, t.v2, t.v0);
}

void Rasterizer::DrawLine(PixelShader& ps, OutputMerger& om, Vertex& from, Vertex& to)
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

void Rasterizer::DrawTriangle(PixelShader& ps, OutputMerger& om, Triangle<Vertex>& t)
{
	DrawTriangle(ps, om, t.v0, t.v1, t.v2);
}

void Rasterizer::DrawTriangle(PixelShader& ps, OutputMerger& om, Vertex& v0, Vertex& v1, Vertex& v2)
{
	if (v0.sv_pos.y > v1.sv_pos.y) std::swap(v0, v1);
	if (v0.sv_pos.y > v2.sv_pos.y) std::swap(v0, v2);
	if (v1.sv_pos.y > v2.sv_pos.y) std::swap(v1, v2);

	Vertex vTopMiddle = v1 - v0;
	Vertex vTopBottom = v2 - v0;
	float yRatio = (v1.sv_pos.y - v0.sv_pos.y) / (v2.sv_pos.y - v0.sv_pos.y);
	Vertex split = vTopBottom * yRatio + v0;

	if (split.sv_pos.x > v1.sv_pos.x) std::swap(split, v1);
	DrawFlatTopTriangle(ps, om, split, v1, v2);
	DrawFlatBottomTriangle(ps, om, v1, split, v0);
}

void Rasterizer::DrawFlatTopTriangle(PixelShader& ps, OutputMerger& om, Vertex& left, Vertex& right, Vertex& bottom)
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

		DrawScanLine(ps, om, iLeft, iRight);
	}
}

void Rasterizer::DrawFlatBottomTriangle(PixelShader& ps, OutputMerger& om, Vertex& right, Vertex& left, Vertex& top)
{
	int yFrom = (int)top.sv_pos.y;
	int yTo = (int)right.sv_pos.y;

	Vertex vTopLeft = left - top;
	Vertex vTopRight = right - top;

	for (int y = yFrom; y < yTo; y++)
	{
		float yRatio = (float)(y - yFrom) / (yTo - yFrom);
		Vertex iLeft = vTopLeft * yRatio + top;
		Vertex iRight = vTopRight * yRatio + top;

		DrawScanLine(ps, om, iLeft, iRight);
	}
}

void Rasterizer::DrawScanLine(PixelShader& ps, OutputMerger& om, Vertex& iLeft, Vertex& iRight)
{
	int xFrom = (int)floorf(iLeft.sv_pos.x + 0.5f);
	int xTo = (int)ceilf(iRight.sv_pos.x + 0.5f);

	auto step = (iRight - iLeft) / (float)(xTo - xFrom);

	for (; xFrom < xTo; xFrom++, iLeft += step)
	{
		auto vertex = iLeft;
		vertex.tc /= vertex.sv_pos.z;
		om.PutPixel((UINT)vertex.sv_pos.x, (UINT)vertex.sv_pos.y, vertex.sv_pos.z, ps(vertex));
	}
}