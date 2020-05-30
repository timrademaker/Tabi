#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING

namespace tabi
{
    namespace math
    {
        class vec2
        {
        public:
            vec2() : x(0), y(0) {}
            vec2(float a_X, float a_Y) : x(a_X), y(a_Y) {}

            /**** Operators ****/
            float& operator[](const unsigned int a_Index);
            float operator[](const unsigned int a_Index) const;

            vec2& operator=(const vec2& a_Rhs);

            bool operator==(const vec2& a_Rhs);
            bool operator!=(const vec2& a_Rhs);

            vec2& operator+=(const vec2& a_Rhs);
            vec2& operator+=(const float a_Rhs);
            
            vec2& operator-=(const vec2& a_Rhs);
            vec2& operator-=(const float a_Rhs);

            vec2& operator*=(const vec2& a_Rhs);
            vec2& operator*=(const float a_Scalar);
            
            vec2& operator/=(const vec2& a_Rhs);
            vec2& operator/=(const float a_Scalar);

            friend vec2 operator+(const vec2& a_Lhs, const vec2& a_Rhs);
            friend vec2 operator+(const vec2& a_Lhs, const float a_Rhs);

            friend vec2 operator-(const vec2& a_Lhs, const vec2& a_Rhs);
            friend vec2 operator-(const vec2& a_Lhs, const float a_Rhs);

            friend vec2 operator*(const vec2& a_Lhs, const vec2& a_Rhs);
            friend vec2 operator*(const vec2& a_Lhs, const float a_Rhs);

            friend vec2 operator/(const vec2& a_Lhs, const vec2& a_Rhs);
            friend vec2 operator/(const vec2& a_Lhs, const float a_Rhs);

        public:
            union
            {
                struct
                {
                    float x;
                    float y;
                };

                float v[2];
            };
        };
    }
}

DISABLE_WARNING_POP