#pragma once
#include "../core/Graphics.h"
#include "DynamicVertex.h"

class Rasterizer
{
private:
	// temporary code
	const Vector3 defaultColor = { 1.0f ,0.0f, 0.34f };

public:
	void DrawLine(Graphics& gfx, const DVTX::Vertex& from, const DVTX::Vertex& to);
};