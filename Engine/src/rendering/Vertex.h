#pragma once
#include "../utility/Vector.h"

class PNVertex
{
public:
	Vector4 sv_pos;
	Vector3 pos;
	Vector3 n;

public:
	PNVertex operator +(const PNVertex& rhs) {
		return { sv_pos + rhs.sv_pos, pos + rhs.pos, n + rhs.n };
	}
	PNVertex& operator +=(const PNVertex& rhs) {
		return *this = *this + rhs;
	}
	PNVertex operator -(const PNVertex& rhs) {
		return { sv_pos - rhs.sv_pos, pos - rhs.pos, n - rhs.n };
	}
	PNVertex& operator -=(const PNVertex& rhs) {
		return *this = *this - rhs;
	}
	PNVertex operator *(const float factor) {
		return { sv_pos * factor, pos * factor, n * factor };
	}
	PNVertex& operator *=(const float factor) {
		return *this = *this * factor;
	}
	PNVertex operator /(const float factor) {
		return { sv_pos / factor, pos / factor, n / factor };
	}
	PNVertex& operator /=(const float factor) {
		return *this = *this / factor;
	}
};