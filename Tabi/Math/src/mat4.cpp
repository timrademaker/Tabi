#include "mat4.h"

#include "vec3.h"
#include "vec4.h"

#include <cmath>
#include <cassert>

using namespace tabi::math;

tabi::math::mat4::mat4()
{
    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            if (i == j)
            {
                m[i][j] = 1.0f;
            }
            else
            {
                m[i][j] = 0.0f;
            }
        }
    }
}

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

    identity.m[0][0] = 1.0f;
    identity.m[1][1] = 1.0f;
    identity.m[2][2] = 1.0f;
    identity.m[3][3] = 1.0f;

    return identity;
}

void tabi::math::mat4::Scale(const float a_Scale)
{
    m[0][0] *= a_Scale;
    m[1][1] *= a_Scale;
    m[2][2] *= a_Scale;
}

void tabi::math::mat4::Scale(const vec3& a_Scale)
{
    m[0][0] *= a_Scale.x;
    m[1][1] *= a_Scale.y;
    m[2][2] *= a_Scale.z;
}

void tabi::math::mat4::Scale(const vec4& a_Scale)
{
    m[0][0] *= a_Scale.x;
    m[1][1] *= a_Scale.y;
    m[2][2] *= a_Scale.z;
    m[3][3] *= a_Scale.w;
}

mat4 tabi::math::mat4::Scale(const mat4& a_Matrix, const float a_Scale)
{
    mat4 result = a_Matrix;

    result.m[0][0] *= a_Scale;
    result.m[1][1] *= a_Scale;
    result.m[2][2] *= a_Scale;

    return result;
}

mat4 tabi::math::mat4::Scale(const mat4& a_Matrix, const vec3& a_Scale)
{
    mat4 result = a_Matrix;

    result.m[0][0] *= a_Scale.x;
    result.m[1][1] *= a_Scale.y;
    result.m[2][2] *= a_Scale.z;

    return result;
}

mat4 tabi::math::mat4::Scale(const mat4& a_Matrix, const vec4& a_Scale)
{
    mat4 result = a_Matrix;

    result.m[0][0] *= a_Scale.x;
    result.m[1][1] *= a_Scale.y;
    result.m[2][2] *= a_Scale.z;
    result.m[3][3] *= a_Scale.w;


    return result;
}

void tabi::math::mat4::Translate(const vec3& a_Translation)
{
    m[0][3] += a_Translation.x;
    m[0][3] += a_Translation.y;
    m[0][3] += a_Translation.z;
}

void tabi::math::mat4::Translate(const vec4& a_Translation)
{
    assert(a_Translation.w != 0.0f);
    m[0][3] += a_Translation.x / a_Translation.w;
    m[0][3] += a_Translation.y / a_Translation.w;
    m[0][3] += a_Translation.z / a_Translation.w;
}

mat4 tabi::math::mat4::Translate(const mat4& a_Matrix, const vec3& a_Translation)
{
    mat4 result = a_Matrix;
    
    result.Translate(a_Translation);

    return result;
}

mat4 tabi::math::mat4::Translate(const mat4& a_Matrix, const vec4& a_Translation)
{
    assert(a_Translation.w != 0);
    mat4 result = a_Matrix;

    result.Translate(a_Translation);

    return result;
}

void tabi::math::mat4::RotateX(const float a_Radians)
{
    const float c = std::cos(a_Radians);
    const float s = std::sin(a_Radians);
    mat4 rotation = mat4::Identity();

    rotation.m[1][1] = c;
    rotation.m[1][2] = -s;
    rotation.m[2][1] = s;
    rotation.m[2][2] = c;

    *this *= rotation;
}

void tabi::math::mat4::RotateY(const float a_Radians)
{
    const float c = std::cos(a_Radians);
    const float s = std::sin(a_Radians);
    mat4 rotation = mat4::Identity();

    rotation.m[0][0] = c;
    rotation.m[0][2] = s;
    rotation.m[2][0] = -s;
    rotation.m[2][2] = c;

    *this *= rotation;
}

void tabi::math::mat4::RotateZ(const float a_Radians)
{
    const float c = std::cos(a_Radians);
    const float s = std::sin(a_Radians);
    mat4 rotation = mat4::Identity();

    rotation.m[0][0] = c;
    rotation.m[0][1] = -s;
    rotation.m[1][0] = s;
    rotation.m[1][1] = c;

    *this *= rotation;
}

mat4 tabi::math::mat4::RotateX(const mat4& a_Matrix, const float a_Radians)
{
    mat4 result = a_Matrix;
    result.RotateX(a_Radians);

    return result;
}

mat4 tabi::math::mat4::RotateY(const mat4& a_Matrix, const float a_Radians)
{
    mat4 result = a_Matrix;
    result.RotateY(a_Radians);

    return result;
}

mat4 tabi::math::mat4::RotateZ(const mat4& a_Matrix, const float a_Radians)
{
    mat4 result = a_Matrix;
    result.RotateZ(a_Radians);

    return result;
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

mat4& mat4::operator=(const mat4& a_Rhs)
{
    for (auto i = 0; i < 16; ++i)
    {
        v[i] = a_Rhs.v[i];
    }

    return *this;
}

bool mat4::operator==(const mat4& a_Rhs)
{
    for (auto i = 0; i < 16; ++i)
    {
        if (v[i] != a_Rhs.v[i])
        {
            return false;
        }
    }

    return true;
}

bool mat4::operator!=(const mat4& a_Rhs)
{
    return !(*this == a_Rhs);
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
    vec4 result = a_Lhs * vec4(a_Rhs, 1.0f);
    return vec3(result.x, result.y, result.z);
}

vec4 tabi::math::operator*(const mat4& a_Lhs, const vec4& a_Rhs)
{
    vec4 result;

    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            result[i] += a_Lhs.m[j][i] * a_Rhs[i];
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
            result.m[i][j] = 0.0f;

            for (auto k = 0; k < 4; ++k)
            {
                result.m[i][j] += a_Lhs.m[i][k] * a_Rhs.m[k][j];
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
