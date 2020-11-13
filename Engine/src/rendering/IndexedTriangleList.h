#pragma once
#include "../utility/Vector.h"
#include <vector>

struct Vertex
{
	Vector3 pos;
};

class IndexedTriangleList
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int > indices;
};