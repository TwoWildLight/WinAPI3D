#pragma once
#include "../utility/Vector.h"

class PNTVertex
{
public:
	Vector4 sv_pos;
	Vector3 pos;
	Vector3 n;
	Vector2 tc;

public:
	PNTVertex operator +(const PNTVertex& rhs) {
		return { sv_pos + rhs.sv_pos, pos + rhs.pos, n + rhs.n, tc + rhs.tc };
	}
	PNTVertex& operator +=(const PNTVertex& rhs) {
		return *this = *this + rhs;
	}
	PNTVertex operator -(const PNTVertex& rhs) {
		return { sv_pos - rhs.sv_pos, pos - rhs.pos, n - rhs.n, tc - rhs.tc };
	}
	PNTVertex& operator -=(const PNTVertex& rhs) {
		return *this = *this - rhs;
	}
	PNTVertex operator *(const float factor) {
		return { sv_pos * factor, pos * factor, n * factor, tc * factor };
	}
	PNTVertex& operator *=(const float factor) {
		return *this = *this * factor;
	}
	PNTVertex operator /(const float factor) {
		return { sv_pos / factor, pos / factor, n / factor, tc / factor };
	}
	PNTVertex& operator /=(const float factor) {
		return *this = *this / factor;
	}
};