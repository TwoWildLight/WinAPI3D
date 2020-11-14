#pragma once
#include "IndexedTriangleList.h"

class Tessellator
{
	using Vertex = DVTX::Vertex;

public:
	std::vector<Triangle<Vertex>> Tessellate(IndexedTriangleList& itList)
	{
		std::vector<Triangle<Vertex>> triangles;
		for (size_t i = 0; i < itList.indices.size(); i += 3u)
		{
			triangles.push_back(Triangle<Vertex>{ 
				itList.vb[itList.indices[i + 0]], 
				itList.vb[itList.indices[i + 1]], 
				itList.vb[itList.indices[i + 2]] });
		}
		return std::move(triangles);
	}
};