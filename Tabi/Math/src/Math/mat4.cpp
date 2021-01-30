#include "Math/mat4.h"

#include "Math/vec3.h"
#include "Math/vec4.h"

#include <cmath>
#include <cassert>

using namespace tabi;

tabi::mat4::mat4()
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

mat4 tabi::mat4::Transpose() const
{
    mat4 transpose;
    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            transpose.m[j][i] = m[i][j];
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

void tabi::mat4::Scale(const float a_Scale)
{
    m[0][0] *= a_Scale;
    m[1][1] *= a_Scale;
    m[2][2] *= a_Scale;
}

void tabi::mat4::Scale(const vec3& a_Scale)
{
    m[0][0] *= a_Scale.x;
    m[1][1] *= a_Scale.y;
    m[2][2] *= a_Scale.z;
}

void tabi::mat4::Scale(const vec4& a_Scale)
{
    m[0][0] *= a_Scale.x;
    m[1][1] *= a_Scale.y;
    m[2][2] *= a_Scale.z;
    m[3][3] *= a_Scale.w;
}

mat4 tabi::mat4::Scale(const mat4& a_Matrix, const float a_Scale)
{
    mat4 result = a_Matrix;

    result.m[0][0] *= a_Scale;
    result.m[1][1] *= a_Scale;
    result.m[2][2] *= a_Scale;

    return result;
}

mat4 tabi::mat4::Scale(const mat4& a_Matrix, const vec3& a_Scale)
{
    mat4 result = a_Matrix;

    result.m[0][0] *= a_Scale.x;
    result.m[1][1] *= a_Scale.y;
    result.m[2][2] *= a_Scale.z;

    return result;
}

mat4 tabi::mat4::Scale(const mat4& a_Matrix, const vec4& a_Scale)
{
    mat4 result = a_Matrix;

    result.m[0][0] *= a_Scale.x;
    result.m[1][1] *= a_Scale.y;
    result.m[2][2] *= a_Scale.z;
    result.m[3][3] *= a_Scale.w;


    return result;
}

vec3 mat4::GetScale() const
{
    return vec3(m[0][0], m[1][1], m[2][2]);
}

void mat4::SetScale(const vec3& a_Scale)
{
    m[0][0] = a_Scale.x;
    m[1][1] = a_Scale.y;
    m[2][2] = a_Scale.z;
}

mat4 mat4::SetScale(const mat4& a_Matrix, const vec3& a_Scale)
{
    mat4 result = a_Matrix;
    result.SetScale(a_Scale);

    return result;
}

void tabi::mat4::Translate(const vec3& a_Translation)
{
    m[3][0] += a_Translation.x;
    m[3][1] += a_Translation.y;
    m[3][2] += a_Translation.z;
}

void tabi::mat4::Translate(const vec4& a_Translation)
{
    assert(a_Translation.w != 0.0f);
    m[3][0] += a_Translation.x / a_Translation.w;
    m[3][1] += a_Translation.y / a_Translation.w;
    m[3][2] += a_Translation.z / a_Translation.w;
}

mat4 tabi::mat4::Translate(const mat4& a_Matrix, const vec3& a_Translation)
{
    mat4 result = a_Matrix;
    
    result.Translate(a_Translation);

    return result;
}

mat4 tabi::mat4::Translate(const mat4& a_Matrix, const vec4& a_Translation)
{
    assert(a_Translation.w != 0);
    mat4 result = a_Matrix;

    result.Translate(a_Translation);

    return result;
}

vec3 mat4::GetPosition() const
{
    return vec3(m[3][0], m[3][1], m[3][2]);
}

void mat4::SetPosition(const vec3& a_Position)
{
    m[3][0] = a_Position.x;
    m[3][1] = a_Position.y;
    m[3][2] = a_Position.z;
}

mat4 mat4::SetPosition(const mat4& a_Matrix, const vec3& a_Position)
{
    mat4 result = a_Matrix;
    result.SetPosition(a_Position);

    return result;
}

void tabi::mat4::RotateX(const float a_Radians)
{
    const float c = std::cos(a_Radians);
    const float s = std::sin(a_Radians);
    mat4 rotation = mat4::Identity();

    rotation.m[1][1] = c;
    rotation.m[2][1] = -s;
    rotation.m[1][2] = s;
    rotation.m[2][2] = c;

    *this *= rotation;
}

void tabi::mat4::RotateY(const float a_Radians)
{
    const float c = std::cos(a_Radians);
    const float s = std::sin(a_Radians);
    mat4 rotation = mat4::Identity();

    rotation.m[0][0] = c;
    rotation.m[2][0] = s;
    rotation.m[0][2] = -s;
    rotation.m[2][2] = c;

    *this *= rotation;
}

void tabi::mat4::RotateZ(const float a_Radians)
{
    const float c = std::cos(a_Radians);
    const float s = std::sin(a_Radians);
    mat4 rotation = mat4::Identity();

    rotation.m[0][0] = c;
    rotation.m[1][0] = -s;
    rotation.m[0][1] = s;
    rotation.m[1][1] = c;

    *this *= rotation;
}

mat4 tabi::mat4::RotateX(const mat4& a_Matrix, const float a_Radians)
{
    mat4 result = a_Matrix;
    result.RotateX(a_Radians);

    return result;
}

mat4 tabi::mat4::RotateY(const mat4& a_Matrix, const float a_Radians)
{
    mat4 result = a_Matrix;
    result.RotateY(a_Radians);

    return result;
}

mat4 tabi::mat4::RotateZ(const mat4& a_Matrix, const float a_Radians)
{
    mat4 result = a_Matrix;
    result.RotateZ(a_Radians);

    return result;
}

void mat4::SetRotation(const vec3& a_EulerRotation)
{
    mat4 newRotMat = mat4::Identity();
    newRotMat.RotateX(a_EulerRotation.x);
    newRotMat.RotateY(a_EulerRotation.y);
    newRotMat.RotateZ(a_EulerRotation.z);

    v[0] = newRotMat[0];
    v[1] = newRotMat[1];
    v[2] = newRotMat[2];
    v[4] = newRotMat[4];
    v[5] = newRotMat[5];
    v[6] = newRotMat[6];
    v[8] = newRotMat[8];
    v[9] = newRotMat[9];
    v[10] = newRotMat[10];
}

mat4 mat4::SetRotation(const mat4& a_Matrix, const vec3& a_EulerRotation)
{
    mat4 result = a_Matrix;
    result.SetRotation(a_EulerRotation);

    return result;
}

mat4 tabi::mat4::CreateTransformationMatrix(const mat4& a_Translation, const mat4& a_Scale, const mat4& a_Rotation)
{
    return a_Scale * a_Rotation * a_Translation;
}

mat4 tabi::mat4::CreatePerspectiveProjectionMatrix(const float a_FoV, const float a_AspectRatio, const float a_Near, const float a_Far)
{
    mat4 result = mat4::Identity();

    const float scaleY = 1.0f / (tan(a_FoV / 2.0f));
    const float scaleX = scaleY / a_AspectRatio;
    const float frustumDepth = a_Far - a_Near;

    result.m[0][0] = scaleX;
    result.m[1][1] = scaleY;
    result.m[2][2] = -(a_Far + a_Near) / frustumDepth;
    result.m[2][3] = -1.0f;
    result.m[3][2] = (-2.0f * a_Far * a_Near) / frustumDepth;
    result.m[3][3] = 0.0f;


    return result;
}

// RHS lookat
mat4 tabi::mat4::CreateLookAtMatrix(const vec3& a_Eye, const vec3& a_Target, const vec3& a_Up)
{
    mat4 result = mat4::Identity();

    vec3 forward = vec3::Normalize(a_Target - a_Eye);
    vec3 right = vec3::Normalize(vec3::Cross(forward, a_Up));
    vec3 up = vec3::Cross(right, forward);

    result.m[0][0] = right.x;
    result.m[1][0] = right.y;
    result.m[2][0] = right.z;
    result.m[0][1] = up.x;
    result.m[1][1] = up.y;
    result.m[2][1] = up.z;
    result.m[0][2] = -forward.x;
    result.m[1][2] = -forward.y;
    result.m[2][2] = -forward.z;

    result.m[3][0] = -vec3::Dot(right, a_Eye);
    result.m[3][1] = -vec3::Dot(up, a_Eye);
    result.m[3][2] =  vec3::Dot(forward, a_Eye);

    return result;
}

void tabi::mat4::LookAt(const vec3& a_Target)
{
    const vec3 forward = vec3::Normalize(GetPosition() - a_Target);
    const vec3 right = vec3::Normalize(vec3::Cross(forward, vec3(0, 1, 0)));
    const vec3 up = vec3::Normalize(vec3::Cross(right, forward));
    v[0] = right.x;
    v[1] = up.x;
    v[2] = forward.x;
    v[4] = right.y;
    v[5] = up.y;
    v[6] = forward.y;
    v[8] = right.z;
    v[9] = up.z;
    v[10] = forward.z;
}

mat4 tabi::mat4::LookAt(const vec3& a_Target) const
{
    mat4 result = *this;

    result.LookAt(a_Target);

    return result;
}

tabi::vec3 tabi::mat4::GetForward() const
{
    return -vec3(v[2], v[6], v[10]);
}

tabi::vec3 tabi::mat4::GetRight() const
{
    return -vec3(v[0], v[4], v[8]);
}

tabi::vec3 tabi::mat4::GetUp() const
{
    return -vec3(v[1], v[5], v[9]);
}

float& tabi::mat4::Get(const unsigned int a_Row, const unsigned int a_Column)
{
    assert(a_Row < 4);
    assert(a_Column < 4);

    return m[a_Row][a_Column];
}

float tabi::mat4::Get(const unsigned int a_Row, const unsigned int a_Column) const
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

bool mat4::operator==(const mat4& a_Rhs) const
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

bool mat4::operator!=(const mat4& a_Rhs) const
{
    return !(*this == a_Rhs);
}

mat4 tabi::operator+(const mat4& a_Lhs, const mat4& a_Rhs)
{
    mat4 res;

    for (auto i = 0; i < 16; ++i)
    {
        res[i] = a_Lhs[i] + a_Rhs[i];
    }

    return res;
}

mat4 tabi::operator-(const mat4& a_Lhs, const mat4& a_Rhs)
{
    mat4 res;
    
    for (auto i = 0; i < 16; ++i)
    {
        res[i] = a_Lhs[i] - a_Rhs[i];
    }

    return res;
}

mat4& tabi::mat4::operator+=(const mat4& a_Rhs)
{
    *this = *this + a_Rhs;

    return *this;
}

mat4& tabi::mat4::operator-=(const mat4& a_Rhs)
{
    *this = *this - a_Rhs;

    return *this;
}

mat4 tabi::operator*(const mat4& a_Lhs, const float a_Scalar)
{
    mat4 result;
    for (auto i = 0; i < 16; ++i)
    {
        result[i] = a_Lhs[i] * a_Scalar;
    }

    return result;
}

vec3 tabi::operator*(const mat4& a_Lhs, const vec3& a_Rhs)
{
    vec4 result = a_Lhs * vec4(a_Rhs, 1.0f);
    return vec3(result.x / result.w, result.y / result.w, result.z / result.w);
}

vec4 tabi::operator*(const mat4& a_Lhs, const vec4& a_Rhs)
{
    vec4 result;

    for (auto i = 0; i < 4; ++i)
    {
        for (auto j = 0; j < 4; ++j)
        {
            result[i] += a_Lhs.m[i][j] * a_Rhs[j];
        }
    }
    
    return result;
}

mat4 tabi::operator*(const mat4& a_Lhs, const mat4& a_Rhs)
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

mat4& tabi::mat4::operator*=(const float a_Scalar)
{
    *this = *this * a_Scalar;

    return *this;
}

mat4& tabi::mat4::operator*=(const mat4& a_Rhs)
{
    *this = *this * a_Rhs;

    return *this;
}
