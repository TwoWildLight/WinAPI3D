#pragma once
#include "DynamicVertex.h"

class Graphics;

class ScreenTransformer
{
public:
	void Transform(const Graphics& gfx, DVTX::Vertex v);
};