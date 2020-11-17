#pragma once
#include "../utility/Vector.h"

class Vertex
{
public:
	Vector4 sv_pos;
	Vector3 pos;
	Vector3 n;
	Vector2 tc;

public:
	Vertex operator +(const Vertex& rhs) {
		return { sv_pos + rhs.sv_pos, pos + rhs.pos, n + rhs.n, tc + rhs.tc };
	}
	Vertex& operator +=(const Vertex& rhs) {
		return *this = *this + rhs;
	}
	Vertex operator -(const Vertex& rhs) {
		return { sv_pos - rhs.sv_pos, pos - rhs.pos, n - rhs.n, tc - rhs.tc };
	}
	Vertex& operator -=(const Vertex& rhs) {
		return *this = *this - rhs;
	}
	Vertex operator *(const float factor) {
		return { sv_pos * factor, pos * factor, n * factor, tc * factor };
	}
	Vertex& operator *=(const float factor) {
		return *this = *this * factor;
	}
	Vertex operator /(const float factor) {
		return { sv_pos / factor, pos / factor, n / factor, tc / factor };
	}
	Vertex& operator /=(const float factor) {
		return *this = *this / factor;
	}
};