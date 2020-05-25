#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING

namespace tabi
{
    namespace math
    {
        class mat4
        {
        public:
            mat4() = default;
            ~mat4() = default;

            mat4& operator+=(const mat4& a_Rhs);
            mat4& operator-=(const mat4& a_Rhs);

            mat4& operator*=(const float a_Scalar);
            mat4& operator*=(const mat4& a_Rhs);

        public:
            union
            {
                float m[4][4];
                float v[16];
            };
        };

        mat4 operator*(const mat4& a_Lhs, const float a_Scalar);
        mat4 operator*(const mat4& a_Lhs, const mat4& a_Rhs);
        mat4 operator+(const mat4& a_Lhs, const mat4& a_Rhs);
        mat4 operator-(const mat4& a_Lhs, const mat4& a_Rhs);

    }
}

DISABLE_WARNING_POP