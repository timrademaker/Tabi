#include "Math/vec3.h"
#include "Math/vec2.h"

#include <cassert>

#include <cmath>

namespace tabi
{
    vec3::vec3(const vec2& a_Vec2, float a_Z)
        : x(a_Vec2.x), y(a_Vec2.y), z(a_Z)
    {
    }

    float tabi::vec3::Dot(const vec3& a_Other) const
    {
        return Dot(*this, a_Other);
    }

    vec3 tabi::vec3::Cross(const vec3& a_Other) const
    {
        return Cross(*this, a_Other);
    }

    void tabi::vec3::Normalize()
    {
        *this /= Length();
    }

    float tabi::vec3::Dot(const vec3& a_Vec1, const vec3& a_Vec2)
    {
        return (a_Vec1.x * a_Vec2.x) + (a_Vec1.y * a_Vec2.y) + (a_Vec1.z * a_Vec2.z);
    }

    vec3 tabi::vec3::Cross(const vec3& a_Vec1, const vec3& a_Vec2)
    {
        return vec3(
            a_Vec1.y * a_Vec2.z - a_Vec1.z * a_Vec2.y,
            a_Vec1.z * a_Vec2.x - a_Vec1.x * a_Vec2.z,
            a_Vec1.x * a_Vec2.y - a_Vec1.y * a_Vec2.x
        );;
    }

    vec3 tabi::vec3::Normalize(const vec3& a_Vector)
    {
        return a_Vector / a_Vector.Length();
    }

    float tabi::vec3::Length() const
    {
        return std::sqrt(LengthSquared());
    }

    float tabi::vec3::LengthSquared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

    vec3 tabi::vec3::Up()
    {
        return vec3(0.0f, 1.0f, 0.0f);
    }

    vec3 tabi::vec3::Right()
    {
        return vec3(1.0f, 0.0f, 0.0f);
    }

    vec3 tabi::vec3::Forward()
    {
        return vec3(0.0f, 0.0f, -1.0f);
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

    bool vec3::operator==(const vec3& a_Rhs) const
    {
        return (x == a_Rhs.x) && (y == a_Rhs.y) && (z == a_Rhs.z);
    }

    bool vec3::operator!=(const vec3& a_Rhs) const
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

    vec3 vec3::operator-() const
    {
        return vec3(-x, -y, -z);
    }

    vec3 operator*(const vec3& a_Lhs, const vec3& a_Rhs)
    {
        return tabi::vec3(a_Lhs.x * a_Rhs.x, a_Lhs.y * a_Rhs.y, a_Lhs.z * a_Rhs.z);
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
}