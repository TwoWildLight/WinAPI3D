#pragma once
#include "IndexedTriangleList.h"

class Graphics;

class ScreenTransformer
{
public:
	static void Transform(const Graphics& gfx, Vertex& v);
	static void Transform(const Graphics& gfx, Triangle<Vertex>& t);
};