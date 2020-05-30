#include "Math/vec3.h"

#include <cassert>

#include <cmath>

using namespace tabi;

float tabi::vec3::dot(const vec3& a_Other) const
{
    return (x * a_Other.x) + (y * a_Other.y) + (z * a_Other.z);
}

vec3 tabi::vec3::cross(const vec3& a_Other) const
{
    return vec3(
        y * a_Other.z - z * a_Other.y,
        z * a_Other.x - x * a_Other.z,
        x * a_Other.y - y * a_Other.x
    );
}

float tabi::vec3::length() const
{
    return std::sqrt(lengthSquared());
}

float tabi::vec3::lengthSquared() const
{
    return (x * x) + (y * y) + (z * z);
}

/**** Operators ****/
float vec3::operator[](const unsigned int a_Index) const
{
    assert(a_Index < 3);
    return v[a_Index];
}

float& vec3::operator[](const unsigned int a_Index)
{
    assert(a_Index < 3);
    return v[a_Index];
}

vec3& vec3::operator=(const vec3& a_Rhs)
{
    x = a_Rhs.x;
    y = a_Rhs.y;
    z = a_Rhs.z;
    return *this;
}

bool vec3::operator==(const vec3& a_Rhs)
{
    return (x == a_Rhs.x) && (y == a_Rhs.y) && (z == a_Rhs.z);
}

bool vec3::operator!=(const vec3& a_Rhs)
{
    return !(*this == a_Rhs);
}

vec3& vec3::operator+=(const vec3& a_Rhs)
{
    x += a_Rhs.x;
    y += a_Rhs.y;
    z += a_Rhs.z;
    return *this;
}

vec3& vec3::operator+=(const float a_Rhs)
{
    x += a_Rhs;
    y += a_Rhs;
    z += a_Rhs;
    return *this;
}

vec3& vec3::operator-=(const vec3& a_Rhs)
{
    x -= a_Rhs.x;
    y -= a_Rhs.y;
    z -= a_Rhs.z;
    return *this;
}

vec3& vec3::operator-=(const float a_Rhs)
{
    x -= a_Rhs;
    y -= a_Rhs;
    z -= a_Rhs;
    return *this;
}

vec3& vec3::operator*=(const vec3& a_Rhs)
{
    x *= a_Rhs.x;
    y *= a_Rhs.y;
    z *= a_Rhs.z;
    return *this;
}

vec3& vec3::operator*=(const float a_Scalar)
{
    x *= a_Scalar;
    y *= a_Scalar;
    z *= a_Scalar;
    return *this;
}

vec3& vec3::operator/=(const vec3& a_Rhs)
{
    x /= a_Rhs.x;
    y /= a_Rhs.y;
    z /= a_Rhs.z;
    return *this;
}

vec3& vec3::operator/=(const float a_Scalar)
{
    x /= a_Scalar;
    y /= a_Scalar;
    z /= a_Scalar;
    return *this;
}

vec3 operator+(const vec3& a_Lhs, const vec3& a_Rhs)
{
    return vec3(a_Lhs.x + a_Rhs.x, a_Lhs.y + a_Rhs.y, a_Lhs.z + a_Rhs.z);
}

vec3 operator+(const vec3& a_Lhs, const float a_Rhs)
{
    return vec3(a_Lhs.x + a_Rhs, a_Lhs.y + a_Rhs, a_Lhs.z + a_Rhs);
}

vec3 operator-(const vec3& a_Lhs, const vec3& a_Rhs)
{
    return vec3(a_Lhs.x - a_Rhs.x, a_Lhs.y - a_Rhs.y, a_Lhs.z - a_Rhs.z);
}

vec3 operator-(const vec3& a_Lhs, const float a_Rhs)
{
    return vec3(a_Lhs.x - a_Rhs, a_Lhs.y - a_Rhs, a_Lhs.z - a_Rhs);
}

vec3 operator*(const vec3& a_Lhs, const vec3& a_Rhs)
{
    return vec3(a_Lhs.x * a_Rhs.x, a_Lhs.y * a_Rhs.y, a_Lhs.z * a_Rhs.z);
}

vec3 operator*(const vec3& a_Lhs, const float a_Rhs)
{
    return vec3(a_Lhs.x * a_Rhs, a_Lhs.y * a_Rhs, a_Lhs.z * a_Rhs);
}

vec3 operator/(const vec3& a_Lhs, const vec3& a_Rhs)
{
    return vec3(a_Lhs.x / a_Rhs.x, a_Lhs.y / a_Rhs.y, a_Lhs.z / a_Rhs.z);
}

vec3 operator/(const vec3& a_Lhs, const float a_Rhs)
{
    return vec3(a_Lhs.x / a_Rhs, a_Lhs.y / a_Rhs, a_Lhs.z / a_Rhs);
}