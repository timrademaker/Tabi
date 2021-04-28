#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING

namespace tabi
{
    class vec4
    {
    public:
        vec4() : x(0), y(0), z(0), w(0) {}
        vec4(float a_X, float a_Y, float a_Z, float a_W) : x(a_X), y(a_Y), z(a_Z), w(a_W) {}
        vec4(const class vec3& a_Vec3, float a_W);

        float Dot(const vec4& a_Other) const;
        void Normalize();

        static float Dot(const vec4& a_Vec1, const vec4& a_Vec2);
        static vec4 Normalize(const vec4& a_Vector);

        float Length() const;
        float LengthSquared() const;

        /**
         * Get the element with the lowest value from the vector
         * @return The minimum element
         */
        float MinElement() const;
        /**
         * Get the element with the highest value from the vector
         * @return The maximum element
         */
        float MaxElement() const;

        /**** Operators ****/
        float& operator[](const unsigned int a_Index);
        float operator[](const unsigned int a_Index) const;

        vec4& operator=(const vec4& a_Rhs);

        bool operator==(const vec4& a_Rhs) const;
        bool operator!=(const vec4& a_Rhs) const;

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
        vec4 operator-() const;

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

            struct
            {
                float r;
                float g;
                float b;
                float a;
            };

            float v[4];
        };
    };
}

DISABLE_WARNING_POP