#pragma once
#include "IndexedTriangleList.h"

class Cube
{
public:
	static IndexedTriangleList Generate(float size)
	{
		std::vector<Vertex> vertices;
		float side = size / 2.0f;
		vertices.push_back({ {-side, side, -side} }); // near
		vertices.push_back({ {side, side, -side} });
		vertices.push_back({ {side, -side, -side} });
		vertices.push_back({ {-side, -side, -side} });

		vertices.push_back({ {-side, side, side} }); // left
		vertices.push_back({ {-side, side, -side} });
		vertices.push_back({ {-side, -side, -side} });
		vertices.push_back({ {-side, -side, side} });

		vertices.push_back({ {side, side, side} }); // far
		vertices.push_back({ {-side, side, side} });
		vertices.push_back({ {-side, -side, side} });
		vertices.push_back({ {side, -side, side} });

		vertices.push_back({ {side, side, -side} }); // right
		vertices.push_back({ {side, side, side} });
		vertices.push_back({ {side, -side, side} });
		vertices.push_back({ {side, -side, -side} });

		vertices.push_back({ {-side, side, side} }); // top
		vertices.push_back({ {side, side, side} });
		vertices.push_back({ {side, side, -side} });
		vertices.push_back({ {-side, side, -side} });

		vertices.push_back({ {side, -side, side} }); // bottom
		vertices.push_back({ {-side, -side, side} });
		vertices.push_back({ {-side, -side, -side} });
		vertices.push_back({ {side, -side, -side} });

		return { std::move(vertices), {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9 ,10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20
		} };
	}
};