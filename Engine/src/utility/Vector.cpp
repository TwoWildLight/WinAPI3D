#include "Vector.h"

Vector2 Vector2::operator+(const Vector2& rhs)
{
    return { x + rhs.x, y + rhs.y };
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    return *this = *this + rhs;
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
    return { x - rhs.x, y - rhs.y };
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    return *this = *this - rhs;
}

Vector2 Vector2::operator*(const float factor)
{
    return { x * factor, y * factor };
}

Vector2& Vector2::operator*=(const float factor)
{
    return *this = *this * factor;
}

Vector2 Vector2::operator/(const float factor)
{
    return { x / factor, y / factor };
}

Vector2& Vector2::operator/=(const float factor)
{
    return *this = *this / factor;
}

Vector3 Vector3::operator+(const Vector3& rhs)
{
    return { x + rhs.x, y + rhs.y, z + rhs.z };
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
    return *this = *this + rhs;
}

Vector3 Vector3::operator-(const Vector3& rhs)
{
    return { x - rhs.x, y - rhs.y, z - rhs.z };
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
    return *this = *this - rhs;
}

Vector3 Vector3::operator*(const float factor)
{
    return { x * factor, y * factor, z * factor };
}

Vector3& Vector3::operator*=(const float factor)
{
    return *this = *this * factor;
}

Vector3 Vector3::operator/(const float factor)
{
    return { x / factor, y / factor, z / factor };
}

Vector3& Vector3::operator/=(const float factor)
{
    return *this = *this / factor;
}