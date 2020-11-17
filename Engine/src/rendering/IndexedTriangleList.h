#pragma once
#include "Vertex.h"
#include "../utility/Vector.h"
#include <vector>

template <typename V>
struct Triangle
{
	V v0, v1, v2;
};

class IndexedTriangleList
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vertex& operator [](size_t index)
	{
		return vertices[indices[index]];
	}

public:
	void GenerateIndividualFaceNormals()
	{
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto& v0 = vertices[indices[i + 0]];
			auto& v1 = vertices[indices[i + 1]];
			auto& v2 = vertices[indices[i + 2]];

			v0.n = v1.n = v2.n = Vector3::Cross(v1.pos - v0.pos, v2.pos - v0.pos);
		}
	}
};