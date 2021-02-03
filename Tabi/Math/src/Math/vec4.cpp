#include "Math/vec4.h"

#include "Math/vec3.h"

#include <cassert>
#include <cmath>

namespace tabi
{
    tabi::vec4::vec4(const vec3& a_Vec3, float a_W)
        : x(a_Vec3.x), y(a_Vec3.y), z(a_Vec3.z), w(a_W)
    {
    }

    float vec4::Dot(const vec4& a_Other) const
    {
        return Dot(*this, a_Other);
    }

    void vec4::Normalize()
    {
        *this /= Length();
    }

    float vec4::Dot(const vec4& a_Vec1, const vec4& a_Vec2)
    {
        return (a_Vec1.x * a_Vec2.x) + (a_Vec1.y * a_Vec2.y) + (a_Vec1.z * a_Vec2.z) + (a_Vec1.w * a_Vec2.w);
    }

    vec4 vec4::Normalize(const vec4& a_Vector)
    {
        return a_Vector / a_Vector.Length();
    }

    float vec4::Length() const
    {
        return std::sqrt(LengthSquared());
    }

    float vec4::LengthSquared() const
    {
        return (x * x) + (y * y) + (z * z) + (w * w);
    }

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

    bool vec4::operator==(const vec4& a_Rhs) const
    {
        return (x == a_Rhs.x) && (y == a_Rhs.y) && (z == a_Rhs.z) && (w == a_Rhs.w);
    }
    bool vec4::operator!=(const vec4& a_Rhs) const
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

    vec4 vec4::operator-() const
    {
        return vec4(-x, -y, -z, -w);
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
}
