#pragma once
#include <vector>
#include "IndexedTriangleList.h"

class TriangleAssembler
{
public:
	static std::vector<Triangle<Vertex>> Assemble(IndexedTriangleList& itList);
};