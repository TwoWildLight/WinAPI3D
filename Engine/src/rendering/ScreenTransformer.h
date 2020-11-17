#pragma once
#include "Vertex.h"

class Graphics;

class ScreenTransformer
{
public:
	static void Transform(const Graphics& gfx, Vertex& v);
};