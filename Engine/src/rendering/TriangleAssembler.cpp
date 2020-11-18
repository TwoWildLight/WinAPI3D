#include "../utility/Matrix.h"
#include "TriangleAssembler.h"

const std::pair<Triangle<Vertex>, Triangle<Vertex>> Clip1(Vertex& v0, Vertex& v1, Vertex& v2)
{
	// calculate alpha values for getting adjusted vertices
	const float alphaA = (-v0.sv_pos.z) / (v1.sv_pos.z - v0.sv_pos.z);
	const float alphaB = (-v0.sv_pos.z) / (v2.sv_pos.z - v0.sv_pos.z);
	const auto v0a = v0 + (v1 - v0) * alphaA;
	const auto v0b = v0 + (v2 - v0) * alphaB;
	return std::make_pair(Triangle<Vertex>{ v0a, v1, v2 }, Triangle<Vertex>{ v0b, v0a, v2 });
};
const Triangle<Vertex> Clip2(Vertex& v0, Vertex& v1, Vertex& v2)
{
	// calculate alpha values for getting adjusted vertices
	const float alpha0 = (-v0.sv_pos.z) / (v2.sv_pos.z - v0.sv_pos.z);
	const float alpha1 = (-v1.sv_pos.z) / (v2.sv_pos.z - v1.sv_pos.z);
	v0 = v0 + (v2 - v0) * alpha0;
	v1 = v1 + (v2 - v1) * alpha1;
	return Triangle<Vertex>{ v0, v1, v2 };
};

std::vector<Triangle<Vertex>> TriangleAssembler::Assemble(IndexedTriangleList& itList)
{
    std::vector<Triangle<Vertex>> triangles;

    for (size_t i = 0; i < itList.indices.size(); i += 3)
    {
		auto& v0 = itList[i + 0];
		auto& v1 = itList[i + 1];
		auto& v2 = itList[i + 2];

		if (Vector3::Dot(Vector3::Cross(v1.sv_pos - v0.sv_pos, v2.sv_pos - v0.sv_pos), v0.sv_pos ) > 0.0f)
			continue;

		// Culling
		if ((v0.sv_pos.x > v0.sv_pos.w && v1.sv_pos.x > v1.sv_pos.w && v2.sv_pos.x > v2.sv_pos.w) ||
			(v0.sv_pos.x < -v0.sv_pos.w && v1.sv_pos.x < -v1.sv_pos.w && v2.sv_pos.x < -v2.sv_pos.w) ||
			(v0.sv_pos.y > v0.sv_pos.w && v1.sv_pos.y > v1.sv_pos.w && v2.sv_pos.y > v2.sv_pos.w) ||
			(v0.sv_pos.y < -v0.sv_pos.w && v1.sv_pos.y < -v1.sv_pos.w && v2.sv_pos.y < -v2.sv_pos.w) ||
			(v0.sv_pos.z > v0.sv_pos.w && v1.sv_pos.z > v1.sv_pos.w && v2.sv_pos.z > v2.sv_pos.w) ||
			(v0.sv_pos.z < 0.0f && v1.sv_pos.z < 0.0f && v2.sv_pos.z < 0.0f))
				continue;

		triangles.push_back({ v0, v1, v2 });
    }

    return std::move(triangles);
}