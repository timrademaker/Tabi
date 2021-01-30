#include "Math/mat4.h"
#include "Math/vec2.h"
#include "Math/vec3.h"
#include "Math/vec4.h"

#include "gtest/gtest.h"

namespace MathPredicates
{
    ::testing::AssertionResult Mat4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::mat4 a_Outcome, const  tabi::mat4 a_Expected);
    ::testing::AssertionResult Mat4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::mat4 a_Outcome, const  tabi::mat4 a_Expected, const float a_Epsilon);
    
    ::testing::AssertionResult Vec2Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::vec2 a_Outcome, const  tabi::vec2 a_Expected);
    ::testing::AssertionResult Vec2Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::vec2 a_Outcome, const  tabi::vec2 a_Expected, const float a_Epsilon);
    
    ::testing::AssertionResult Vec3Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::vec3 a_Outcome, const  tabi::vec3 a_Expected);
    ::testing::AssertionResult Vec3Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::vec3 a_Outcome, const  tabi::vec3 a_Expected, const float a_Epsilon);
    
    ::testing::AssertionResult Vec4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const tabi::vec4 a_Outcome, const  tabi::vec4 a_Expected);
    ::testing::AssertionResult Vec4Equal(const char* a_Outcome_Expression, const char* a_Expected_Expression, const char* a_Epsilon_Expression, const tabi::vec4 a_Outcome, const  tabi::vec4 a_Expected, const float a_Epsilon);
}
