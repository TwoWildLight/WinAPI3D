#pragma once
#include "Vertex.h"

class Graphics;

class ScreenTransformer
{
public:
	void Transform(const Graphics& gfx, PNTVertex& v);
};