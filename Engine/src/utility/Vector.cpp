#include "Vector.h"
#include "Matrix.h"
#include <cmath>

float Vector2::Length() const
{
    return sqrtf(x * x + y * y);
}

void Vector2::Normalize()
{
    *this = Normalize(*this);
}

float Vector2::Dot(const Vector2& v) const
{
    return Dot(*this, v);
}

Vector2 Vector2::Normalize(const Vector2& v)
{
    return v / v.Length();
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return { x + rhs.x, y + rhs.y };
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    return *this = *this + rhs;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return { x - rhs.x, y - rhs.y };
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    return *this = *this - rhs;
}

Vector2 Vector2::operator*(const float factor) const
{
    return { x * factor, y * factor };
}

Vector2& Vector2::operator*=(const float factor)
{
    return *this = *this * factor;
}

Vector2 Vector2::operator/(const float factor) const
{ 
    return { x / factor, y / factor };
}

Vector2& Vector2::operator/=(const float factor)
{
    return *this = *this / factor;
}

float Vector3::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

void Vector3::Normalize()
{
    *this = Normalize(*this);
}

float Vector3::Dot(const Vector3& v) const
{
    return Dot(*this, v);
}

Vector3 Vector3::Cross(const Vector3& v) const
{
    return Cross(*this, v);
}

Vector3 Vector3::Normalize(const Vector3& v)
{
    return v / v.Length();
}

float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
    return { lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x };
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
    return { x + rhs.x, y + rhs.y, z + rhs.z };
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
    return *this = *this + rhs;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
    return { x - rhs.x, y - rhs.y, z - rhs.z };
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
    return *this = *this - rhs;
}

Vector3 Vector3::operator*(const float factor) const
{
    return { x * factor, y * factor, z * factor };
}

Vector3& Vector3::operator*=(const float factor)
{
    return *this = *this * factor;
}

Vector3 Vector3::operator/(const float factor) const
{
    return { x / factor, y / factor, z / factor };
}

Vector3& Vector3::operator/=(const float factor)
{
    return *this = *this / factor;
}

Vector3 Vector3::operator*(const Matrix& m) const
{
    return{
        m.cells[0][0] * x + m.cells[1][0] * y + m.cells[2][0] * z + m.cells[3][0],
        m.cells[0][1] * x + m.cells[1][1] * y + m.cells[2][1] * z + m.cells[3][1],
        m.cells[0][2] * x + m.cells[1][2] * y + m.cells[2][2] * z + m.cells[3][2]
    };
}

Vector3& Vector3::operator*=(const Matrix& m)
{
    return *this = *this * m;
}

Vector4 Vector4::operator*(const Matrix& m) const
{
    return{
        m.cells[0][0] * x + m.cells[1][0] * y + m.cells[2][0] * z + m.cells[3][0],
        m.cells[0][1] * x + m.cells[1][1] * y + m.cells[2][1] * z + m.cells[3][1],
        m.cells[0][2] * x + m.cells[1][2] * y + m.cells[2][2] * z + m.cells[3][2],
        m.cells[0][3] * x + m.cells[1][3] * y + m.cells[2][3] * z + m.cells[3][3]
    };
}

Vector4& Vector4::operator*=(const Matrix& m)
{
 
    return *this = *this * m;
}