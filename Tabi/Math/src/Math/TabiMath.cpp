#include "Math/TabiMath.h"

#include <cmath>

constexpr float oneDegreeInRadians = static_cast<float>(PI / 180.0f);
constexpr float oneRadianInDegrees = static_cast<float>(180.0f / PI);

using namespace tabi;

float tabi::DegToRad(const float a_Degrees)
{
    return a_Degrees * oneDegreeInRadians;
}

float tabi::RadToDeg(const float a_Radians)
{
    return a_Radians * oneRadianInDegrees;
}
