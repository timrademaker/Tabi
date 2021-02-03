#include "Precidates.h"

#include "Math/vec2.h"

#include "gtest/gtest.h"

/** Tests for vector functions */

TEST(Vec2Tests, DotProduct)
{
    // Same vector
    {
        {
            const float expected = 1.25f;
            const tabi::vec2 vec(1.0f, 0.5f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }

        {
            const float expected = 1.0f;
            const tabi::vec2 vec(0.0f, 1.0f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }

        {
            const float expected = 0.25f;
            const tabi::vec2 vec(0.5f, 0.0f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }
    }

    // Opposite vector
    {
        const float expected = -1.25f;

        const tabi::vec2 vec(1.0f, 0.5f);
        const tabi::vec2 negativeVec = -vec;

        EXPECT_FLOAT_EQ(vec.Dot(negativeVec), expected);
    }

    // Perpendicular vector and zero-vector
    {
        const float expected = 0.0f;

        const tabi::vec2 firstVector(1.0f, 0.0f);
        const tabi::vec2 secondVector(0.0f, 0.0f);
        const tabi::vec2 thirdVector(0.0f, 1.0f);

        EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        EXPECT_FLOAT_EQ(firstVector.Dot(thirdVector), expected);
    }

    // Other
    {
        {
            const float expected = -7.65f;

            const tabi::vec2 firstVector(8.0f, -2.5f);
            const tabi::vec2 secondVector(1.7f, 8.5f);

            EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        }

        {
            const float expected = 0.5f;

            const tabi::vec2 firstVector(1.0f, 0.0f);
            const tabi::vec2 secondVector(0.5f, 0.0f);

            EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        }
    }
}

TEST(Vec2Tests, Normalization)
{
    // One axis
    {
        const tabi::vec2 expected(1.0f, 0.0f);
        
        tabi::vec2 outcome(100.0f, 0.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, outcome, expected);
    }

    // Two axes
    {
        const tabi::vec2 expected(0.8944271909999159f, 0.4472135954999579f);

        tabi::vec2 outcome(100.0f, 50.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, outcome, expected);
    }
}

TEST(Vec2Tests, Length)
{
    // One axis
    {
        const float expected = 123.4f;
        const tabi::vec2 outcome(expected, 0.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }

    // Two axes
    {
        const float expected = 111.80339887498948f;
        const tabi::vec2 outcome(100.0f, 50.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }
}
