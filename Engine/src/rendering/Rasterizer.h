#pragma once
#include "IndexedTriangleList.h"

class PixelShader;
class OutputMerger;

class Rasterizer
{
private:
	bool bCullBackface = true;

public:
	void DrawLine(PixelShader& ps, OutputMerger& om, PNVertex& from, PNVertex& to);
	void DrawTriangle(PixelShader& ps, OutputMerger& om, Triangle<PNVertex> t);

private:
	void DrawTriangle(PixelShader& ps, OutputMerger& om, PNVertex& v0, PNVertex& v1, PNVertex& v2);
	void DrawFlatTopTriangle(PixelShader& ps, OutputMerger& om, PNVertex& left, PNVertex& right, PNVertex& bottom);
	void DrawFlatBottomTriangle(PixelShader& ps, OutputMerger& om, PNVertex& right, PNVertex& left, PNVertex& top);
	void DrawScanLine(PixelShader& ps, OutputMerger& om, PNVertex& iLeft, PNVertex& iRight, int y);
};