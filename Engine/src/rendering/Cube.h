#pragma once
#include "IndexedTriangleList.h"

class Cube
{
public:
	static IndexedTriangleList CreateCube(float size = 1.0f)
	{
		std::vector<PNVertex> vertices(24);

		const float side = size / 2.0f;
		vertices[0].pos = { -side, side, -side }; // near
		vertices[1].pos = { side, side, -side };
		vertices[2].pos = { side, -side, -side };
		vertices[3].pos = { -side, -side, -side };
		vertices[4].pos = { -side, side, side }; // left
		vertices[5].pos = { -side, side, -side };
		vertices[6].pos = { -side, -side, -side };
		vertices[7].pos = { -side, -side, side };
		vertices[8].pos = { side, side, side }; // far
		vertices[9].pos = { -side, side, side };
		vertices[10].pos = { -side, -side, side };
		vertices[11].pos = { side, -side, side };
		vertices[12].pos = { side, side, -side }; // right
		vertices[13].pos = { side, side, side };
		vertices[14].pos = { side, -side, side };
		vertices[15].pos = { side, -side, -side };
		vertices[16].pos = { -side, side, side }; // top
		vertices[17].pos = { side, side, side };
		vertices[18].pos = { side, side, -side };
		vertices[19].pos = { -side, side, -side };
		vertices[20].pos = { side, -side, side }; // bottom
		vertices[21].pos = { -side, -side, side };
		vertices[22].pos = { -side, -side, -side };
		vertices[23].pos = { side, -side, -side };

		return { std::move(vertices), {
			0,1,2,2,3,0,
			4,5,6,6,7,4,
			8,9,10,10,11,8,
			12,13,14,14,15,12,
			16,17,18,18,19,16,
			20,21,22,22,23,20
			} };
	}
};