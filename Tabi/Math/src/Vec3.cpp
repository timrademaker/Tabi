#include "vec3.h"

using namespace tabi::math;

float tabi::math::vec3::dot(const vec3 a_Other) const
{
    return (x * a_Other.x) + (y * a_Other.y) + (z * a_Other.z);
}

vec3 tabi::math::vec3::cross(const vec3 a_Other) const
{
    return vec3(
        y * a_Other.z - z * a_Other.y,
        z * a_Other.x - x * a_Other.z,
        x * a_Other.y - y * a_Other.x
    );
}