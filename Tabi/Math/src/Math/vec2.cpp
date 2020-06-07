#include "Math/vec2.h"

#include <cassert>

using namespace tabi;

/**** Operators ****/
float& vec2::operator[](const unsigned int a_Index)
{
    assert(a_Index < 2);
    return v[a_Index];
}

float vec2::operator[](const unsigned int a_Index) const
{
    assert(a_Index < 2);
    return v[a_Index];
}

vec2& vec2::operator=(const vec2& a_Rhs)
{
    x = a_Rhs.x;
    y = a_Rhs.y;
    
    return *this;
}

bool vec2::operator==(const vec2& a_Rhs)
{
    return (x == a_Rhs.x) && (y == a_Rhs.y);
}
bool vec2::operator!=(const vec2& a_Rhs)
{
    return !(*this == a_Rhs);
}

vec2& vec2::operator+=(const vec2& a_Rhs)
{
    x += a_Rhs.x;
    y += a_Rhs.y;
    return *this;
}

vec2& vec2::operator+=(const float a_Rhs)
{
    x += a_Rhs;
    y += a_Rhs;
    return *this;
}

vec2& vec2::operator-=(const vec2& a_Rhs)
{
    x -= a_Rhs.x;
    y -= a_Rhs.y;
    return *this;
}

vec2& vec2::operator-=(const float a_Rhs)
{
    x -= a_Rhs;
    y -= a_Rhs;
    return *this;
}

vec2& vec2::operator*=(const vec2& a_Rhs)
{
    x *= a_Rhs.x;
    y *= a_Rhs.y;
    return *this;
}

vec2& vec2::operator*=(const float a_Scalar)
{
    x *= a_Scalar;
    y *= a_Scalar;
    return *this;
}

vec2& vec2::operator/=(const vec2& a_Rhs)
{
    x /= a_Rhs.x;
    y /= a_Rhs.y;
    return *this;
}

vec2& vec2::operator/=(const float a_Scalar)
{
    x /= a_Scalar;
    y /= a_Scalar;
    return *this;
}

vec2 operator+(const vec2& a_Lhs, const vec2& a_Rhs)
{
    return vec2(a_Lhs.x + a_Rhs.y, a_Lhs.y + a_Rhs.y);
}

vec2 operator+(const vec2& a_Lhs, const float a_Rhs)
{
    return vec2(a_Lhs.x + a_Rhs, a_Lhs.y + a_Rhs);
}

vec2 operator-(const vec2& a_Lhs, const vec2& a_Rhs)
{
    return vec2(a_Lhs.x - a_Rhs.y, a_Lhs.y - a_Rhs.y);
}

vec2 operator-(const vec2& a_Lhs, const float a_Rhs)
{
    return vec2(a_Lhs.x - a_Rhs, a_Lhs.y - a_Rhs);
}

vec2 vec2::operator-()
{
    return vec2(-x, -y);
}

vec2 operator*(const vec2& a_Lhs, const vec2& a_Rhs)
{
    return vec2(a_Lhs.x * a_Rhs.x, a_Lhs.x * a_Rhs.x);
}

vec2 operator*(const vec2& a_Lhs, const float a_Rhs)
{
    return vec2(a_Lhs.x * a_Rhs, a_Lhs.x * a_Rhs);
}

vec2 operator/(const vec2& a_Lhs, const vec2& a_Rhs)
{
    return vec2(a_Lhs.x / a_Rhs.x, a_Lhs.x / a_Rhs.x);
}

vec2 operator/(const vec2& a_Lhs, const float a_Rhs)
{
    return vec2(a_Lhs.x / a_Rhs, a_Lhs.x / a_Rhs);
}