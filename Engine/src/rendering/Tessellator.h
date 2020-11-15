#pragma once
#include "IndexedTriangleList.h"

class Tessellator
{
public:
	std::vector<Triangle<PNVertex>> Tessellate(IndexedTriangleList& itList)
	{
		std::vector<Triangle<PNVertex>> triangles;
		for (size_t i = 0; i < itList.indices.size(); i += 3u)
		{
			triangles.push_back(Triangle<PNVertex>{
				itList.vertices[itList.indices[i + 0]], 
				itList.vertices[itList.indices[i + 1]], 
				itList.vertices[itList.indices[i + 2]]
			});
		}
		return std::move(triangles);
	}
};