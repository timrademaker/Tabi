#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING


namespace tabi
{
    namespace math
    {
        class vec3
        {
        public:
            vec3() : x(0), y(0), z(0) {}
            vec3(float a_X, float a_Y, float a_Z) : x(a_X), y(a_Y), z(a_Z) {}

            float dot(const vec3 a_Other) const;
            vec3 cross(const vec3 a_Other) const;

            // TODO: Operators

        public:
            union
            {
                struct
                {
                    float x;
                    float y;
                    float z;
                };

                struct
                {
                    float r;
                    float g;
                    float b;
                };

                struct
                {
                    float m_X;
                    float m_Y;
                    float m_Z;
                };

                float v[3];
            };
            
        };

    }
}

DISABLE_WARNING_POP