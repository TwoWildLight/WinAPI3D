#pragma once
#include "DynamicVertex.h"
#include "../utility/Vector.h"

class OutputMerger;

class Rasterizer
{
private:
	// temporary code
	const Vector3 defaultColor = { 1.0f ,0.0f, 0.34f };

public:
	void DrawLine(OutputMerger& om, const DVTX::Vertex& from, const DVTX::Vertex& to);
};