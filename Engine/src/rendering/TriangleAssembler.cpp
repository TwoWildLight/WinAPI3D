#include "../utility/Matrix.h"
#include "TriangleAssembler.h"

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

		// NDC Culling
		if (v0.sv_pos.x > v0.sv_pos.w && v1.sv_pos.x > v1.sv_pos.w && v2.sv_pos.x > v2.sv_pos.w)
			continue;
		if (v0.sv_pos.x < -v0.sv_pos.w && v1.sv_pos.x < -v1.sv_pos.w && v2.sv_pos.x < -v2.sv_pos.w)
			continue;
		if (v0.sv_pos.y > v0.sv_pos.w && v1.sv_pos.y > v1.sv_pos.w && v2.sv_pos.y > v2.sv_pos.w)
			continue;
		if (v0.sv_pos.y < -v0.sv_pos.w && v1.sv_pos.y < -v1.sv_pos.w && v2.sv_pos.y < -v2.sv_pos.w)
			continue;
		if (v0.sv_pos.z > v0.sv_pos.w && v1.sv_pos.z > v1.sv_pos.w && v2.sv_pos.z > v2.sv_pos.w)
			continue;
		if (v0.sv_pos.z < 0.0f && v1.sv_pos.z < 0.0f && v2.sv_pos.z < 0.0f)
			continue;

		triangles.push_back({ v0, v1, v2 });
    }

    return std::move(triangles);
}