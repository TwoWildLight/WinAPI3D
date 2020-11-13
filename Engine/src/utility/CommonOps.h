#pragma once
#include "Vector.h"
#include "Matrix.h"

inline Vector3 operator *(const Vector3& v, const Matrix& m)
{
	return{ 
		m.cells[0][0] * v.x + m.cells[1][0] * v.y + m.cells[2][0] * v.z + m.cells[3][0],
		m.cells[0][1] * v.x + m.cells[1][1] * v.y + m.cells[2][1] * v.z + m.cells[3][1],
		m.cells[0][2] * v.x + m.cells[1][2] * v.y + m.cells[2][2] * v.z + m.cells[3][2]
	};
}

inline Vector3& operator *=(Vector3& v, const Matrix& m)
{
	return v = v * m;
}