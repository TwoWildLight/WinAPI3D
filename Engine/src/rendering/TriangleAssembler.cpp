#include "../utility/Matrix.h"
#include "TriangleAssembler.h"

std::vector<Triangle<Vertex>> TriangleAssembler::Assemble(IndexedTriangleList& itList, const Matrix& mProj)
{
    std::vector<Triangle<Vertex>> triangles;

    for (size_t i = 0; i < itList.indices.size(); i += 3)
    {
		auto& v0 = itList[i + 0];
		auto& v1 = itList[i + 1];
		auto& v2 = itList[i + 2];

		Vector4 eyepos = Vector4(0.0f, 0.0f, 0.0f, 1.0f) * mProj;
		if (Vector3::Dot(Vector3::Cross(v1.sv_pos - v0.sv_pos, v2.sv_pos - v0.sv_pos), v0.sv_pos - eyepos ) > 0.0f)
			continue;

		// Culling
		if ((v0.sv_pos.x > v0.sv_pos.w && v1.sv_pos.x > v1.sv_pos.w && v2.sv_pos.x > v2.sv_pos.w) ||
			(v0.sv_pos.x < -v0.sv_pos.w && v1.sv_pos.x < -v1.sv_pos.w && v2.sv_pos.x < -v2.sv_pos.w) ||
			(v0.sv_pos.y > v0.sv_pos.w && v1.sv_pos.y > v1.sv_pos.w && v2.sv_pos.y > v2.sv_pos.w) ||
			(v0.sv_pos.y < -v0.sv_pos.w && v1.sv_pos.y < -v1.sv_pos.w && v2.sv_pos.y < -v2.sv_pos.w) ||
			(v0.sv_pos.z > v0.sv_pos.w && v1.sv_pos.z > v1.sv_pos.w && v2.sv_pos.z > v2.sv_pos.w) ||
			(v0.sv_pos.z < 0.0f && v1.sv_pos.z < 0.0f && v2.sv_pos.z < 0.0f)) continue;

		// clipping routines
		const auto Clip1 = [&triangles](Vertex& v0, Vertex& v1, Vertex& v2)
		{
			const auto v0a = v0 + (v1 - v0) * (-v0.sv_pos.z) / (v1.sv_pos.z - v0.sv_pos.z);
			const auto v0b = v0 + (v2 - v0) * (-v0.sv_pos.z) / (v2.sv_pos.z - v0.sv_pos.z);
			triangles.push_back({ v0a, v1, v2 });
			triangles.push_back({ v0b, v0a, v2 });
		};
		const auto Clip2 = [&triangles](Vertex& v0, Vertex& v1, Vertex& v2)
		{
			v0 = v0 + (v2 - v0) * (-v0.sv_pos.z) / (v2.sv_pos.z - v0.sv_pos.z);
			v1 = v1 + (v2 - v1) * (-v1.sv_pos.z) / (v2.sv_pos.z - v1.sv_pos.z);
			triangles.push_back({ v0, v1, v2 });
		};

		// near clipping tests
		if (v0.sv_pos.z < 0.0f)
		{
			if (v1.sv_pos.z < 0.0f) Clip2(v0, v1, v2);
			else if (v2.sv_pos.z < 0.0f) Clip2(v0, v2, v1);
			else Clip1(v0, v1, v2);
		}
		else if (v1.sv_pos.z < 0.0f)
		{
			if (v2.sv_pos.z < 0.0f) Clip2(v1, v2, v0);
			else Clip1(v1, v0, v2);
		}
		else if (v2.sv_pos.z < 0.0f)
		{
			Clip1(v2, v0, v1);
		}
		else
		{
			triangles.push_back({ v0, v1, v2 });
		}
    }

    return std::move(triangles);
}