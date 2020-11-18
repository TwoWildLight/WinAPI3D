#pragma once
#include "IndexedTriangleList.h"

class Graphics;

class NDCScreenTransformer
{
public:
	static void Transform(const Graphics& gfx, Vertex& v);
	static void Transform(const Graphics& gfx, Triangle<Vertex>& t);
};