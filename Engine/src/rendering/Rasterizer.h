#pragma once
#include "IndexedTriangleList.h"

class PixelShader;
class OutputMerger;

class Rasterizer
{
public:
	static void DrawLine(PixelShader& ps, OutputMerger& om, Triangle<Vertex>& t);
	static void DrawTriangle(PixelShader& ps, OutputMerger& om, Triangle<Vertex>& t);

private:
	static void DrawLine(PixelShader& ps, OutputMerger& om, Vertex& from, Vertex& to);
	static void DrawTriangle(PixelShader& ps, OutputMerger& om, Vertex& v0, Vertex& v1, Vertex& v2);
	static void DrawFlatTopTriangle(PixelShader& ps, OutputMerger& om, Vertex& left, Vertex& right, Vertex& bottom);
	static void DrawFlatBottomTriangle(PixelShader& ps, OutputMerger& om, Vertex& right, Vertex& left, Vertex& top);
	static void DrawScanLine(PixelShader& ps, OutputMerger& om, Vertex& iLeft, Vertex& iRight);
};