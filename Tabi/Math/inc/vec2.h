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