#pragma once
#include "DynamicVertex.h"
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
	DVTX::VertexBuffer vb;
	std::vector<unsigned int> indices;

public:
	void GenerateIndependentNormals()
	{
		using Type = DVTX::VertexLayout::Element::Type;
		for (size_t i = 0; i < indices.size(); i += 3)
		{
			auto v0 = vb[indices[i]];
			auto v1 = vb[indices[i + 1]];
			auto v2 = vb[indices[i + 2]];
			const auto p0 = (v0.Attr<Vector3>(Type::POSITION3D));
			const auto p1 = (v1.Attr<Vector3>(Type::POSITION3D));
			const auto p2 = (v2.Attr<Vector3>(Type::POSITION3D));

			const auto n = Vector3::Normalize(Vector3::Cross((p1 - p0), (p2 - p0)));

			v0.Attr<Vector3>(Type::NORMAL) = n;
			v1.Attr<Vector3>(Type::NORMAL) = n;
			v2.Attr<Vector3>(Type::NORMAL) = n;
		}
	}
};