#include "Precidates.h"

#include "Math/vec3.h"

#include "gtest/gtest.h"

/** Tests for vector functions */

TEST(Vec3Tests, DotProduct)
{
    // Same vector
    {
        {
            const float expected = 1.29f;
            const tabi::vec3 vec(1.0f, 0.5f, 0.2f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }

        {
            const float expected = 1.0f;
            const tabi::vec3 vec(0.0f, 1.0f, 0.0f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }

        {
            const float expected = 0.25f;
            const tabi::vec3 vec(0.5f, 0.0f, 0.0f);
            EXPECT_FLOAT_EQ(vec.Dot(vec), expected);
        }
    }

    // Opposite vector
    {
        const float expected = -1.29f;

        const tabi::vec3 vec(1.0f, 0.5f, 0.2f);
        const tabi::vec3 negativeVec = -vec;

        EXPECT_FLOAT_EQ(vec.Dot(negativeVec), expected);
    }

    // Perpendicular vector
    {
        const float expected = 0.0f;

        const tabi::vec3 firstVector(1.0f, 0.0f, 0.0f);
        const tabi::vec3 secondVector(0.0f, 0.0f, 1.0f);
        const tabi::vec3 thirdVector(0.0f, 1.0f, 0.0f);

        EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        EXPECT_FLOAT_EQ(firstVector.Dot(thirdVector), expected);
    }

    // Other
    {
        {
            const float expected = -14.85f;

            const tabi::vec3 firstVector(8.0f, 2.5f, -3.2f);
            const tabi::vec3 secondVector(1.7f, -0.5f, 8.5f);

            EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        }

        {
            const float expected = 0.5f;

            const tabi::vec3 firstVector(1.0f, 0.0f, 0.0f);
            const tabi::vec3 secondVector(0.5f, 0.0f, 0.0f);

            EXPECT_FLOAT_EQ(firstVector.Dot(secondVector), expected);
        }
    }
}

TEST(Vec3Tests, CrossProduct)
{
    {
        const tabi::vec3 expectedAB(0.0f, -1.0f, 0.0f);
        const tabi::vec3 expectedBA = -expectedAB;

        const tabi::vec3 a(1.0f, 0.0f, 0.0f);
        const tabi::vec3 b(0.0f, 0.0f, 1.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, a.Cross(b), expectedAB);
        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, b.Cross(a), expectedBA);
    }

    {
        const tabi::vec3 expectedAB(-3.0f, 6.0f, -3.0f);
        const tabi::vec3 expectedBA = -expectedAB;

        const tabi::vec3 a(1.0f, 2.0f, 3.0f);
        const tabi::vec3 b(4.0f, 5.0f, 6.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, a.Cross(b), expectedAB);
        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, b.Cross(a), expectedBA);
    }
}

TEST(Vec3Tests, Normalization)
{
    // One axis
    {
        const tabi::vec3 expected(1.0f, 0.0f, 0.0f);
        
        tabi::vec3 outcome(100.0f, 0.0f, 0.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outcome, expected);
    }

    // Two axes
    {
        const tabi::vec3 expected(0.8944271909999159f, 0.4472135954999579f, 0.0f);

        tabi::vec3 outcome(100.0f, 50.0f, 0.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outcome, expected);
    }

    // Three axes
    {
        const tabi::vec3 expected(0.3651483716701107f, 0.18257418583505536f, -0.9128709291752768f);

        tabi::vec3 outcome(100.0f, 50.0f, -250.0f);
        outcome.Normalize();

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outcome, expected);
    }
}

TEST(Vec3Tests, Length)
{
    // One axis
    {
        const float expected = 123.4f;
        const tabi::vec3 outcome(123.4f, 0.0f, 0.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }

    // Two axes
    {
        const float expected = 111.80339887498948f;
        const tabi::vec3 outcome(100.0f, 50.0f, 0.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }

    // Three axes
    {
        const float expected = 273.8612787525831f;
        const tabi::vec3 outcome(100.0f, 50.0f, -250.0f);
        EXPECT_FLOAT_EQ(outcome.Length(), expected);
        EXPECT_FLOAT_EQ(outcome.LengthSquared(), expected * expected);
    }
}

TEST(Vec3Tests, MinElement)
{
    {
        const float expected = 100.0f;
        const tabi::vec3 vec{ expected, expected + 0.001f, expected + 1.0f };
        EXPECT_FLOAT_EQ(vec.MinElement(), expected);
    }

    {
        const float expected = -100.0f;
        const tabi::vec3 vec{ expected, expected + 0.001f, expected + 1.0f };
        EXPECT_FLOAT_EQ(vec.MinElement(), expected);
    }
}

TEST(Vec3Tests, MaxElement)
{
    {
        const float expected = 100.0f;
        const tabi::vec3 vec{ expected, expected - 0.001f, expected - 1.0f };
        EXPECT_FLOAT_EQ(vec.MaxElement(), expected);
    }

    {
        const float expected = -100.0f;
        const tabi::vec3 vec{ expected, expected - 0.001f, expected - 1.0f };
        EXPECT_FLOAT_EQ(vec.MaxElement(), expected);
    }
}
