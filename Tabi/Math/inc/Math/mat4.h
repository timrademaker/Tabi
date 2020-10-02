#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING

namespace tabi
{
    class vec3;
    class vec4;

    // Row-major 4x4 matrix
    class mat4
    {
    public:
        mat4();
        ~mat4() = default;

        mat4 Transpose() const;
        static mat4 Identity();

        // Scaling
        void Scale(const float a_Scale);
        void Scale(const vec3& a_Scale);
        void Scale(const vec4& a_Scale);
        static mat4 Scale(const mat4& a_Matrix, const float a_Scale);
        static mat4 Scale(const mat4& a_Matrix, const vec3& a_Scale);
        static mat4 Scale(const mat4& a_Matrix, const vec4& a_Scale);

        vec3 GetScale() const;
        void SetScale(const vec3& a_Scale);
        static mat4 SetScale(const mat4& a_Matrix, const vec3& a_Scale);

        // Translation
        void Translate(const vec3& a_Translation);
        void Translate(const vec4& a_Translation);
        static mat4 Translate(const mat4& a_Matrix, const vec3& a_Translation);
        static mat4 Translate(const mat4& a_Matrix, const vec4& a_Translation);

        vec3 GetPosition() const;
        void SetPosition(const vec3& a_Position);
        static mat4 SetPosition(const mat4& a_Matrix, const vec3& a_Position);


        // Rotation
        void RotateX(const float a_Radians);
        void RotateY(const float a_Radians);
        void RotateZ(const float a_Radians);
        static mat4 RotateX(const mat4& a_Matrix, const float a_Radians);
        static mat4 RotateY(const mat4& a_Matrix, const float a_Radians);
        static mat4 RotateZ(const mat4& a_Matrix, const float a_Radians);

        vec3 GetRotation() const;
        /// Set the rotation of the matrix (in radians)
        void SetRotation(const vec3& a_EulerRotation);
        static mat4 SetRotation(const mat4& a_Matrix, const vec3& a_EulerRotation);

        static mat4 CreateTransformationMatrix(const mat4& a_Translation, const mat4& a_Scale, const mat4& a_Rotation);
        static mat4 CreatePerspectiveProjectionMatrix(const float a_FoV, const float a_AspectRatio, const float a_Near, const float a_Far);
        static mat4 CreateLookAtMatrix(const vec3& a_Eye, const vec3& a_Target, const vec3& a_Up);

        float Get(const unsigned int a_Row, const unsigned int a_Column) const;
        float& Get(const unsigned int a_Row, const unsigned int a_Column);

        /**** Operators ****/
        float operator[](const unsigned int a_Index) const;
        float& operator[](const unsigned int a_Index);

        mat4& operator=(const mat4& a_Rhs);

        bool operator==(const mat4& a_Rhs);
        bool operator!=(const mat4& a_Rhs);

        mat4& operator+=(const mat4& a_Rhs);
        mat4& operator-=(const mat4& a_Rhs);

        mat4& operator*=(const mat4& a_Rhs);
        mat4& operator*=(const float a_Scalar);

        friend mat4 operator*(const mat4& a_Lhs, const float a_Scalar);
        friend vec3 operator*(const mat4& a_Lhs, const vec3& a_Rhs);
        friend vec4 operator*(const mat4& a_Lhs, const vec4& a_Rhs);

        friend mat4 operator*(const mat4& a_Lhs, const mat4& a_Rhs);
        friend mat4 operator+(const mat4& a_Lhs, const mat4& a_Rhs);
        friend mat4 operator-(const mat4& a_Lhs, const mat4& a_Rhs);

    public:
        union
        {
            float m[4][4];
            float v[16];
        };
    };
}


DISABLE_WARNING_POP