#pragma once

namespace tabi
{
    namespace maths
    {
        class vec2
        {
        public:
            vec2() : x(0), y(0) { }
            vec2(float a_X, float a_Y) : x(a_X), y(a_Y) { }

        public:
            float x;
            float y;
        };

        class vec3
        {
        public:
            vec3() : x(0), y(0), z(0) { }
            vec3(float a_X, float a_Y, float a_Z) : x(a_X), y(a_Y), z(a_Z) { }

        public:
            float x;
            float y;
            float z;
        };

        class vec4
        {
        public:
            vec4() : x(0), y(0), z(0), w(0) { }
            vec4(float a_X, float a_Y, float a_Z, float a_W) : x(a_X), y(a_Y), z(a_Z), w(a_W) { }

        public:
            float x;
            float y;
            float z;
            float w;
        };
    }
}