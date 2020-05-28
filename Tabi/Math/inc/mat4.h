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

            float Get(const unsigned int a_Row, const unsigned int a_Column) const;
            float& Get(const unsigned int a_Row, const unsigned int a_Column);

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