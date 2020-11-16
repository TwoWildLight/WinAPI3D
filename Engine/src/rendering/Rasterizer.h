#pragma once
#include "IndexedTriangleList.h"

class PixelShader;
class OutputMerger;

class Rasterizer
{
private:
	bool bCullBackface = true;

public:
	void DrawLine(PixelShader& ps, OutputMerger& om, PNTVertex& from, PNTVertex& to);
	void DrawTriangle(PixelShader& ps, OutputMerger& om, Triangle<PNTVertex> t);

private:
	void DrawTriangle(PixelShader& ps, OutputMerger& om, PNTVertex& v0, PNTVertex& v1, PNTVertex& v2);
	void DrawFlatTopTriangle(PixelShader& ps, OutputMerger& om, PNTVertex& left, PNTVertex& right, PNTVertex& bottom);
	void DrawFlatBottomTriangle(PixelShader& ps, OutputMerger& om, PNTVertex& right, PNTVertex& left, PNTVertex& top);
	void DrawScanLine(PixelShader& ps, OutputMerger& om, PNTVertex& iLeft, PNTVertex& iRight);
};