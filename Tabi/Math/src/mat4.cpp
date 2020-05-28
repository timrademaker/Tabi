#include "mat4.h"

#include "vec3.h"
#include "vec4.h"

#include <cassert>

using namespace tabi::math;

mat4 tabi::math::mat4::Transpose() const
{
    mat4 transpose;
    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            transpose.Get(j, i) = m[i][j];
        }
    }

    return transpose;
}

mat4 mat4::Identity()
{
    mat4 identity;

    identity.Get(0, 0) = 1.0f;
    identity.Get(1, 1) = 1.0f;
    identity.Get(2, 2) = 1.0f;
    identity.Get(3, 3) = 1.0f;

    return identity;
}

float& tabi::math::mat4::Get(const unsigned int a_Row, const unsigned int a_Column)
{
    assert(a_Row < 4);
    assert(a_Column < 4);

    return m[a_Row][a_Column];
}

float tabi::math::mat4::Get(const unsigned int a_Row, const unsigned int a_Column) const
{
    assert(a_Row < 4);
    assert(a_Column < 4);

    return m[a_Row][a_Column];
}


float mat4::operator[](const unsigned int a_Index) const
{
    assert(a_Index < 16);
    return v[a_Index];
}

float& mat4::operator[](const unsigned int a_Index)
{
    assert(a_Index < 16);
    return v[a_Index];
}

mat4 tabi::math::operator+(const mat4& a_Lhs, const mat4& a_Rhs)
{
    mat4 res;

    for (auto i = 0; i < 16; ++i)
    {
        res[i] = a_Lhs[i] + a_Rhs[i];
    }

    return res;
}

mat4 tabi::math::operator-(const mat4& a_Lhs, const mat4& a_Rhs)
{
    mat4 res;
    
    for (auto i = 0; i < 16; ++i)
    {
        res[i] = a_Lhs[i] - a_Rhs[i];
    }

    return res;
}

mat4& tabi::math::mat4::operator+=(const mat4& a_Rhs)
{
    *this = *this + a_Rhs;

    return *this;
}

mat4& tabi::math::mat4::operator-=(const mat4& a_Rhs)
{
    *this = *this - a_Rhs;

    return *this;
}

mat4 tabi::math::operator*(const mat4& a_Lhs, const float a_Scalar)
{
    mat4 result;
    for (auto i = 0; i < 16; ++i)
    {
        result[i] = a_Lhs[i] * a_Scalar;
    }

    return result;
}

vec3 tabi::math::operator*(const mat4& a_Lhs, const vec3& a_Rhs)
{
    vec4 result = a_Lhs * vec4(a_Rhs, 0.0f);
    return vec3(result.x, result.y, result.z);
}

vec4 tabi::math::operator*(const mat4& a_Lhs, const vec4& a_Rhs)
{
    vec4 result;

    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            result[i] += a_Lhs.Get(j, i) * a_Rhs[i];
        }
    }
    
    return result;
}

mat4 tabi::math::operator*(const mat4& a_Lhs, const mat4& a_Rhs)
{
    mat4 result;

    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            result.Get(i, j) = 0.0f;

            for (auto k = 0; k < 4; ++k)
            {
                result.Get(i, j) += a_Lhs.Get(i, k) * a_Rhs.Get(k, j);
            }
        }
    }

    return result;
}

mat4& tabi::math::mat4::operator*=(const float a_Scalar)
{
    *this = *this * a_Scalar;

    return *this;
}

mat4& tabi::math::mat4::operator*=(const mat4& a_Rhs)
{
    *this = *this * a_Rhs;

    return *this;
}
