#include "Math/vec2.h"

#include <cassert>

#include <cmath>

namespace tabi
{
    float tabi::vec2::Dot(const vec2& a_Other) const
    {
        return Dot(*this, a_Other);
    }

    void tabi::vec2::Normalize()
    {
        *this /= Length();
    }

    float tabi::vec2::Dot(const vec2& a_Vec1, const vec2& a_Vec2)
    {
        return (a_Vec1.x * a_Vec2.x) + (a_Vec1.y * a_Vec2.y);
    }

    vec2 tabi::vec2::Normalize(const vec2& a_Vector)
    {
        return a_Vector / a_Vector.Length();
    }

    float tabi::vec2::Length() const
    {
        return std::sqrt(LengthSquared());;
    }

    float tabi::vec2::LengthSquared() const
    {
        return (x * x) + (y * y);
    }

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

    bool vec2::operator==(const vec2& a_Rhs) const
    {
        return (x == a_Rhs.x) && (y == a_Rhs.y);
    }
    bool vec2::operator!=(const vec2& a_Rhs) const
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
        return vec2(a_Lhs.x + a_Rhs.x, a_Lhs.y + a_Rhs.y);
    }

    vec2 operator+(const vec2& a_Lhs, const float a_Rhs)
    {
        return vec2(a_Lhs.x + a_Rhs, a_Lhs.y + a_Rhs);
    }

    vec2 operator-(const vec2& a_Lhs, const vec2& a_Rhs)
    {
        return vec2(a_Lhs.x - a_Rhs.x, a_Lhs.y - a_Rhs.y);
    }

    vec2 operator-(const vec2& a_Lhs, const float a_Rhs)
    {
        return vec2(a_Lhs.x - a_Rhs, a_Lhs.y - a_Rhs);
    }

    vec2 vec2::operator-() const
    {
        return vec2(-x, -y);
    }

    vec2 operator*(const vec2& a_Lhs, const vec2& a_Rhs)
    {
        return vec2(a_Lhs.x * a_Rhs.x, a_Lhs.y * a_Rhs.y);
    }

    vec2 operator*(const vec2& a_Lhs, const float a_Rhs)
    {
        return vec2(a_Lhs.x * a_Rhs, a_Lhs.y * a_Rhs);
    }

    vec2 operator/(const vec2& a_Lhs, const vec2& a_Rhs)
    {
        return vec2(a_Lhs.x / a_Rhs.x, a_Lhs.y / a_Rhs.y);
    }

    vec2 operator/(const vec2& a_Lhs, const float a_Rhs)
    {
        return vec2(a_Lhs.x / a_Rhs, a_Lhs.y / a_Rhs);
    }
}