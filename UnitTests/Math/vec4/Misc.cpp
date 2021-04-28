#include "Precidates.h"

#include "Math/vec4.h"

#include "gtest/gtest.h"

/** Tests for vector functions */

TEST(Vec4Tests, DotProduct)
{
    // Same vector
    {
        {
            const float expected = 1.3f;
            const tabi::vec4 vec(1.0f, 0.5f, 0.2f, 0.1f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }

        {
            const float expected = 1.0f;
            const tabi::vec4 vec(0.0f, 1.0f, 0.0f, 0.0f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }

        {
            const float expected = 0.25f;
            const tabi::vec4 vec(0.5f, 0.0f, 0.0f, 0.0f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }
    }

    // Opposite vector
    {
        const float expected = -1.3f;

        const tabi::vec4 vec(1.0f, 0.5f, 0.2f, 0.1f);
        const tabi::vec4 negativeVec = -vec;

        EXPECT_FLOAT_EQ(vec.Dot(negativeVec), expected);
    }

    // Perpendicular vector
    {
        const float expected = 0.0f;

        const tabi::vec4 firstVector(1.0f, 0.0f, 0.0f, 0.0f);
        const tabi::vec4 secondVector(0.0f, 0.0f, 1.0f, 0.0f);
        const tabi::vec4 thirdVector(0.0f, 1.0f, 0.0f, 0.0f);

        EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        EXPECT_FLOAT_EQ(firstVector.Dot(thirdVector), expected);
    }

    // Other
    {
        {
            const float expected = 27.225f;

            const tabi::vec4 firstVector(8.0f, 2.5f, -3.2f, 15.3f);
            const tabi::vec4 secondVector(1.7f, -0.5f, 8.5f, 2.75f);

            EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        }

        {
            const float expected = 0.5f;

            const tabi::vec4 firstVector(0.0f, 0.0f, 0.0f, 1.0f);
            const tabi::vec4 secondVector(0.0f, 0.0f, 0.0f, 0.5f);

            EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        }
    }
}

TEST(Vec4Tests, Normalization)
{
    // One axis
    {
        const tabi::vec4 expected(1.0f, 0.0f, 0.0f, 0.0f);
        
        tabi::vec4 outcome(100.0f, 0.0f, 0.0f, 0.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, outcome, expected);
    }

    // Two axes
    {
        const tabi::vec4 expected(0.8944271909999159f, 0.4472135954999579f, 0.0f, 0.0f);

        tabi::vec4 outcome(100.0f, 50.0f, 0.0f, 0.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, outcome, expected);
    }

    // Three axes
    {
        const tabi::vec4 expected(0.3651483716701107f, 0.18257418583505536f, -0.9128709291752768f, 0.0f);

        tabi::vec4 outcome(100.0f, 50.0f, -250.0f, 0.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, outcome, expected);
    }

    // Four axes
    {
        const tabi::vec4 expected(0.363894941f, 0.18194747f, -0.909737352f, 0.082786099f);

        tabi::vec4 outcome(100.0f, 50.0f, -250.0f, 22.75f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, outcome, expected);
    }
}

TEST(Vec4Tests, Length)
{
    // One axis
    {
        const float expected = 123.4f;
        const tabi::vec4 outcome(123.4f, 0.0f, 0.0f, 0.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }

    // Two axes
    {
        const float expected = 111.80339887498948f;
        const tabi::vec4 outcome(100.0f, 50.0f, 0.0f, 0.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }

    // Three axes
    {
        const float expected = 273.8612787525831f;
        const tabi::vec4 outcome(100.0f, 50.0f, -250.0f, 0.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }

    // Four axes
    {
        const float expected = 274.80459f;
        const tabi::vec4 outcome(100.0f, 50.0f, -250.0f, 22.75f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }
}

TEST(Vec4Tests, MinElement)
{
    {
        const float expected = 100.0f;
        const tabi::vec4 vec{ expected, expected + 0.001f, expected + 1.0f, expected + 1.5f };
        EXPECT_FLOAT_EQ(vec.MinElement(), expected);
    }

    {
        const float expected = -100.0f;
        const tabi::vec4 vec{ expected, expected + 0.001f, expected + 1.0f, expected + 1.5f };
        EXPECT_FLOAT_EQ(vec.MinElement(), expected);
    }
}

TEST(Vec4Tests, MaxElement)
{
    {
        const float expected = 100.0f;
        const tabi::vec4 vec{ expected, expected - 0.001f, expected - 1.0f, expected - 1.5f };
        EXPECT_FLOAT_EQ(vec.MaxElement(), expected);
    }

    {
        const float expected = -100.0f;
        const tabi::vec4 vec{ expected, expected - 0.001f, expected - 1.0f, expected - 1.5f };
        EXPECT_FLOAT_EQ(vec.MaxElement(), expected);
    }
}
