#pragma once
#include "../utility/Vector.h"

class PNVertex
{
public:
	Vector3 pos;
	Vector3 n;

public:
	PNVertex operator +(const PNVertex& rhs) {
		return { pos + rhs.pos, n + rhs.n };
	}
	PNVertex& operator +=(const PNVertex& rhs) {
		return *this = *this + rhs;
	}
	PNVertex operator -(const PNVertex& rhs) {
		return { pos - rhs.pos, n - rhs.n };
	}
	PNVertex& operator -=(const PNVertex& rhs) {
		return *this = *this - rhs;
	}
	PNVertex operator *(const float factor) {
		return { pos * factor, n * factor };
	}
	PNVertex& operator *=(const float factor) {
		return *this = *this * factor;
	}
	PNVertex operator /(const float factor) {
		return { pos / factor, n / factor };
	}
	PNVertex& operator /=(const float factor) {
		return *this = *this / factor;
	}
};