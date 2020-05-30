#include "Math/vec4.h"

#include "Math/vec3.h"

#include <cassert>

using namespace tabi;


tabi::vec4::vec4(const vec3& a_Vec3, float a_W)
    : x(a_Vec3.x), y(a_Vec3.y), z(a_Vec3.z), w(a_W)
{ }


/**** Operators ****/
float& vec4::operator[](const unsigned int a_Index)
{
    assert(a_Index < 4);
    return v[a_Index];
}

float vec4::operator[](const unsigned int a_Index) const
{
    assert(a_Index < 4);
    return v[a_Index];
}

vec4& vec4::operator=(const vec4& a_Rhs)
{
    x = a_Rhs.x;
    y = a_Rhs.y;
    z = a_Rhs.z;
    w = a_Rhs.w;

    return *this;
}

bool vec4::operator==(const vec4& a_Rhs)
{
    return (x == a_Rhs.x) && (y == a_Rhs.y) && (z == a_Rhs.z) && (w == a_Rhs.w);
}
bool vec4::operator!=(const vec4& a_Rhs)
{
    return !(*this == a_Rhs);
}

vec4& vec4::operator+=(const vec4& a_Rhs)
{
    x += a_Rhs.x;
    y += a_Rhs.y;
    z += a_Rhs.z;
    w += a_Rhs.w;
    return *this;
}

vec4& vec4::operator+=(const float a_Rhs)
{
    x += a_Rhs;
    y += a_Rhs;
    z += a_Rhs;
    w += a_Rhs;
    return *this;
}

vec4& vec4::operator-=(const vec4& a_Rhs)
{
    x -= a_Rhs.x;
    y -= a_Rhs.y;
    z -= a_Rhs.z;
    w -= a_Rhs.w;
    return *this;
}

vec4& vec4::operator-=(const float a_Rhs)
{
    x -= a_Rhs;
    y -= a_Rhs;
    z -= a_Rhs;
    w -= a_Rhs;
    return *this;
}

vec4& vec4::operator*=(const vec4& a_Rhs)
{
    x *= a_Rhs.x;
    y *= a_Rhs.y;
    z *= a_Rhs.z;
    w *= a_Rhs.w;
    return *this;
}

vec4& vec4::operator*=(const float a_Scalar)
{
    x *= a_Scalar;
    y *= a_Scalar;
    z *= a_Scalar;
    w *= a_Scalar;
    return *this;
}

vec4& vec4::operator/=(const vec4& a_Rhs)
{
    x /= a_Rhs.x;
    y /= a_Rhs.y;
    z /= a_Rhs.z;
    w /= a_Rhs.w;
    return *this;
}

vec4& vec4::operator/=(const float a_Scalar)
{
    x /= a_Scalar;
    y /= a_Scalar;
    z /= a_Scalar;
    w /= a_Scalar;
    return *this;
}

vec4 operator+(const vec4& a_Lhs, const vec4& a_Rhs)
{
    return vec4(a_Lhs.x + a_Rhs.x, a_Lhs.y + a_Rhs.y, a_Lhs.z + a_Rhs.z, a_Lhs.w + a_Rhs.w);
}

vec4 operator+(const vec4& a_Lhs, const float a_Rhs)
{
    return vec4(a_Lhs.x + a_Rhs, a_Lhs.y + a_Rhs, a_Lhs.z + a_Rhs, a_Lhs.w + a_Rhs);
}

vec4 operator-(const vec4& a_Lhs, const vec4& a_Rhs)
{
    return vec4(a_Lhs.x - a_Rhs.x, a_Lhs.y - a_Rhs.y, a_Lhs.z - a_Rhs.z, a_Lhs.w - a_Rhs.w);
}

vec4 operator-(const vec4& a_Lhs, const float a_Rhs)
{
    return vec4(a_Lhs.x - a_Rhs, a_Lhs.y - a_Rhs, a_Lhs.z - a_Rhs, a_Lhs.w - a_Rhs);
}

vec4 operator*(const vec4& a_Lhs, const vec4& a_Rhs)
{
    return vec4(a_Lhs.x * a_Rhs.x, a_Lhs.y * a_Rhs.y, a_Lhs.z * a_Rhs.z, a_Lhs.w * a_Rhs.w);
}
vec4 operator*(const vec4& a_Lhs, const float a_Rhs)
{
    return vec4(a_Lhs.x * a_Rhs, a_Lhs.y * a_Rhs, a_Lhs.z * a_Rhs, a_Lhs.w * a_Rhs);
}

vec4 operator/(const vec4& a_Lhs, const vec4& a_Rhs)
{
    return vec4(a_Lhs.x / a_Rhs.x, a_Lhs.y / a_Rhs.y, a_Lhs.z / a_Rhs.z, a_Lhs.w / a_Rhs.w);
}

vec4 operator/(const vec4& a_Lhs, const float a_Rhs)
{
    return vec4(a_Lhs.x / a_Rhs, a_Lhs.y / a_Rhs, a_Lhs.z / a_Rhs, a_Lhs.w / a_Rhs);
}