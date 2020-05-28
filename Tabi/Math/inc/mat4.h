#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING

namespace tabi
{
    namespace math
    {
        class vec3;
        class vec4;

        class mat4
        {
        public:
            mat4() = default;
            ~mat4() = default;

            mat4 Transpose() const;
            static mat4 Identity();

            void Scale(const float a_Scale);
            void Scale(const vec3& a_Scale);
            void Scale(const vec4& a_Scale);
            static mat4 Scale(const mat4& a_Matrix, const float a_Scale);
            static mat4 Scale(const mat4& a_Matrix, const vec3& a_Scale);
            static mat4 Scale(const mat4& a_Matrix, const vec4& a_Scale);

            void Translate(const vec3& a_Translation);
            void Translate(const vec4& a_Translation);
            static mat4 Translate(const mat4& a_Matrix, const vec3& a_Translation);
            static mat4 Translate(const mat4& a_Matrix, const vec4& a_Translation);

            // TODO: Rotation

            float Get(const unsigned int a_Row, const unsigned int a_Column) const;
            float& Get(const unsigned int a_Row, const unsigned int a_Column);
            
            /**** Operators ****/
            float operator[](const unsigned int a_Index) const;
            float& operator[](const unsigned int a_Index);
            
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
}


DISABLE_WARNING_POP