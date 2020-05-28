#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING


namespace tabi
{
    namespace math
    {
        class vec3;

        class vec4
        {
        public:
            vec4() : x(0), y(0), z(0), w(0) {}
            vec4(float a_X, float a_Y, float a_Z, float a_W) : x(a_X), y(a_Y), z(a_Z), w(a_W) {}
            vec4(const vec3& a_Vec3, float a_W);

            /**** Operators ****/
            float& operator[](const unsigned int a_Index);
            float operator[](const unsigned int a_Index) const;

            vec4& operator=(const vec4& a_Rhs);

            bool operator==(const vec4& a_Rhs);
            bool operator!=(const vec4& a_Rhs);

            vec4& operator+=(const vec4& a_Rhs);
            vec4& operator+=(const float a_Rhs);

            vec4& operator-=(const vec4& a_Rhs);
            vec4& operator-=(const float a_Rhs);

            vec4& operator*=(const vec4& a_Rhs);
            vec4& operator*=(const float a_Scalar);

            vec4& operator/=(const vec4& a_Rhs);
            vec4& operator/=(const float a_Scalar);

            friend vec4 operator+(const vec4& a_Lhs, const vec4& a_Rhs);
            friend vec4 operator+(const vec4& a_Lhs, const float a_Rhs);

            friend vec4 operator-(const vec4& a_Lhs, const vec4& a_Rhs);
            friend vec4 operator-(const vec4& a_Lhs, const float a_Rhs);

            friend vec4 operator*(const vec4& a_Lhs, const vec4& a_Rhs);
            friend vec4 operator*(const vec4& a_Lhs, const float a_Rhs);

            friend vec4 operator/(const vec4& a_Lhs, const vec4& a_Rhs);
            friend vec4 operator/(const vec4& a_Lhs, const float a_Rhs);

        public:
            union
            {
                struct
                {
                    float x;
                    float y;
                    float z;
                    float w;
                };

                float v[4];
            };
        };
    }
}

DISABLE_WARNING_POP