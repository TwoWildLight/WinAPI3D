#pragma once
#include "DynamicVertex.h"
#include "../utility/Vector.h"

class PixelShader;
class OutputMerger;

class Rasterizer
{
public:
	void DrawLine(PixelShader& ps, OutputMerger& om, DVTX::Vertex from, DVTX::Vertex to);
};