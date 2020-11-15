#pragma once
#include "IndexedTriangleList.h"

class Cube
{
public:
	static IndexedTriangleList CreateCube(float size = 1.0f)
	{
		using Type = DVTX::VertexLayout::Element::Type;

		DVTX::VertexBuffer vb(DVTX::VertexLayout{}
			.Append(Type::POSITION3D), 
			24u
		);

		const float side = size / 2.0f;
		vb[0].Attr<Vector3>(Type::POSITION3D) = { -side, side, -side }; // near
		vb[1].Attr<Vector3>(Type::POSITION3D) = { side, side, -side };
		vb[2].Attr<Vector3>(Type::POSITION3D) = { side, -side, -side };
		vb[3].Attr<Vector3>(Type::POSITION3D) = { -side, -side, -side };
		vb[4].Attr<Vector3>(Type::POSITION3D) = { -side, side, side }; // left
		vb[5].Attr<Vector3>(Type::POSITION3D) = { -side, side, -side };
		vb[6].Attr<Vector3>(Type::POSITION3D) = { -side, -side, -side };
		vb[7].Attr<Vector3>(Type::POSITION3D) = { -side, -side, side };
		vb[8].Attr<Vector3>(Type::POSITION3D) = { side, side, side }; // far
		vb[9].Attr<Vector3>(Type::POSITION3D) = { -side, side, side };
		vb[10].Attr<Vector3>(Type::POSITION3D) = { -side, -side, side };
		vb[11].Attr<Vector3>(Type::POSITION3D) = { side, -side, side };
		vb[12].Attr<Vector3>(Type::POSITION3D) = { side, side, -side }; // right
		vb[13].Attr<Vector3>(Type::POSITION3D) = { side, side, side };
		vb[14].Attr<Vector3>(Type::POSITION3D) = { side, -side, side };
		vb[15].Attr<Vector3>(Type::POSITION3D) = { side, -side, -side };
		vb[16].Attr<Vector3>(Type::POSITION3D) = { -side, side, side }; // top
		vb[17].Attr<Vector3>(Type::POSITION3D) = { side, side, side };
		vb[18].Attr<Vector3>(Type::POSITION3D) = { side, side, -side };
		vb[19].Attr<Vector3>(Type::POSITION3D) = { -side, side, -side };
		vb[20].Attr<Vector3>(Type::POSITION3D) = { side, -side, side }; // bottom
		vb[21].Attr<Vector3>(Type::POSITION3D) = { -side, -side, side };
		vb[22].Attr<Vector3>(Type::POSITION3D) = { -side, -side, -side };
		vb[23].Attr<Vector3>(Type::POSITION3D) = { side, -side, -side };

		return { std::move(vb), {
			0,1,2,2,3,0,
			4,5,6,6,7,4,
			8,9,10,10,11,8,
			12,13,14,14,15,12,
			16,17,18,18,19,16,
			20,21,22,22,23,20
			} };
	}
};