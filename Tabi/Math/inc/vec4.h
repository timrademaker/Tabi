#pragma once

#include <TabiMacros.h>

DISABLE_WARNING_PUSH
DISABLE_NAMELESS_STRUCT_WARNING


namespace tabi
{
    namespace math
    {
        class vec4
        {
        public:
            vec4() : x(0), y(0), z(0), w(0) {}
            vec4(float a_X, float a_Y, float a_Z, float a_W) : x(a_X), y(a_Y), z(a_Z), w(a_W) {}

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