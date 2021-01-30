#include "Precidates.h"

#include <numeric>

::testing::AssertionResult MathPredicates::Mat4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::mat4 a_Outcome, const tabi::mat4 a_Expected)
{
    return Mat4Equal(a_Outcome_Expression, a_Expected_Expression, "epsilon", a_Outcome, a_Expected, std::numeric_limits<float>::epsilon());
}

::testing::AssertionResult MathPredicates::Mat4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::mat4 a_Outcome, const  tabi::mat4 a_Expected, const float a_Epsilon)
{
    TABI_UNUSED(a_Expected_Expression);
    TABI_UNUSED(a_Epsilon_Expression);

    for (int i = 0; i < 16; ++i)
    {
        if (fabs(a_Outcome[i] - a_Expected[i]) > a_Epsilon)
        {
            return ::testing::AssertionFailure()
                << a_Outcome_Expression << "[" << i << "]"
                << " is " << a_Outcome[i]
                << ", but " << a_Expected[i] << " was expected!";
        }
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult MathPredicates::Vec2Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::vec2 a_Outcome, const tabi::vec2 a_Expected)
{
    return Vec2Equal(a_Outcome_Expression, a_Expected_Expression, "epsilon", a_Outcome, a_Expected, std::numeric_limits<float>::epsilon());
}

::testing::AssertionResult MathPredicates::Vec2Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::vec2 a_Outcome, const  tabi::vec2 a_Expected, const float a_Epsilon)
{
    TABI_UNUSED(a_Expected_Expression);
    TABI_UNUSED(a_Epsilon_Expression);

    if (fabs(a_Outcome.x - a_Expected.x ) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".x"
            << " is " << a_Outcome.x
            << ", but " << a_Expected.x << " was expected!";
    }

    if (fabs(a_Outcome.y - a_Expected.y) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".y"
            << " is " << a_Outcome.y
            << ", but " << a_Expected.y << " was expected!";
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult MathPredicates::Vec3Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::vec3 a_Outcome, const tabi::vec3 a_Expected)
{
    return Vec3Equal(a_Outcome_Expression, a_Expected_Expression, "epsilon", a_Outcome, a_Expected, std::numeric_limits<float>::epsilon());
}

::testing::AssertionResult MathPredicates::Vec3Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::vec3 a_Outcome, const  tabi::vec3 a_Expected, const float a_Epsilon)
{
    TABI_UNUSED(a_Expected_Expression);
    TABI_UNUSED(a_Epsilon_Expression);

    if (fabs(a_Outcome.x - a_Expected.x) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".x"
            << " is " << a_Outcome.x
            << ", but " << a_Expected.x << " was expected!";
    }

    if (fabs(a_Outcome.y - a_Expected.y) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".y"
            << " is " << a_Outcome.y
            << ", but " << a_Expected.y << " was expected!";
    }

    if (fabs(a_Outcome.z - a_Expected.z) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".z"
            << " is " << a_Outcome.z
            << ", but " << a_Expected.z << " was expected!";
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult MathPredicates::Vec4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::vec4 a_Outcome, const tabi::vec4 a_Expected)
{
    return Vec4Equal(a_Outcome_Expression, a_Expected_Expression, "epsilon", a_Outcome, a_Expected, std::numeric_limits<float>::epsilon());
}

::testing::AssertionResult MathPredicates::Vec4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::vec4 a_Outcome, const  tabi::vec4 a_Expected, const float a_Epsilon)
{
    TABI_UNUSED(a_Expected_Expression);
    TABI_UNUSED(a_Epsilon_Expression);

    if (fabs(a_Outcome.x - a_Expected.x) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".x"
            << " is " << a_Outcome.x
            << ", but " << a_Expected.x << " was expected!";
    }

    if (fabs(a_Outcome.y - a_Expected.y) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".y"
            << " is " << a_Outcome.y
            << ", but " << a_Expected.y << " was expected!";
    }

    if (fabs(a_Outcome.z - a_Expected.z) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".z"
            << " is " << a_Outcome.z
            << ", but " << a_Expected.z << " was expected!";
    }

    if (fabs(a_Outcome.w - a_Expected.w) > a_Epsilon)
    {
        return ::testing::AssertionFailure()
            << a_Outcome_Expression << ".w"
            << " is " << a_Outcome.w
            << ", but " << a_Expected.w << " was expected!";
    }

    return ::testing::AssertionSuccess();
}
