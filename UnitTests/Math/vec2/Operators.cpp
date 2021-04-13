#include "Precidates.h"

#include "Math/vec2.h"

#include "gtest/gtest.h"

/** Tests for vector operators */

TEST(Vec2Tests, Addition)
{
    // vec2 + vec2
    {
        const tabi::vec2 expected(-7.0f, 1685.0f);

        // a + b
        const tabi::vec2 firstVector(7.0f, 685.0f);
        const tabi::vec2 secondVector(-14.0f, 1000.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, firstVector + secondVector, expected);

        // a += b
        tabi::vec2 thirdVector = firstVector;
        thirdVector += secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, thirdVector, expected);
    }

    // vec2 + float
    {
        const tabi::vec2 expected(-7.0f, 1685.0f);

        // a + b
        const tabi::vec2 firstVector(-12.0f, 1680.0f);
        const float addedValue = 5.0f;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, firstVector + addedValue, expected);

        // a += b
        tabi::vec2 secondVector = firstVector;
        secondVector += addedValue;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, secondVector, expected);
    }
}

TEST(Vec2Tests, Subtraction)
{
    // vec2 - vec2
    {
        const tabi::vec2 expected(21.0f, -315.0f);

        // a - b
        const tabi::vec2 firstVector(7.0f, 685.0f);
        const tabi::vec2 secondVector(-14.0f, 1000.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, firstVector - secondVector, expected);

        // a -= b
        tabi::vec2 thirdVector = firstVector;
        thirdVector -= secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, thirdVector, expected);
    }

    // vec2 - float
    {
        const tabi::vec2 expected(-3.0f, 11.0f);

        // a - b
        const tabi::vec2 firstVector(2.0f, 16.0f);
        const float subtractedValue = 5.0f;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, firstVector - subtractedValue, expected);

        // a -= b
        tabi::vec2 secondVector = firstVector;
        secondVector -= subtractedValue;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, secondVector, expected);
    }
}

TEST(Vec2Tests, Multiplication)
{
    // vec2 * vec2
    {
        const tabi::vec2 expected(-10.0f, 66.6f);

        // a * b (vec2)
        const tabi::vec2 firstVector(20.0f, 33.3f);
        const tabi::vec2 secondVector(-0.5f, 2.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, firstVector * secondVector, expected);

        // a *= b (vec2)
        tabi::vec2 thirdVector = firstVector;
        thirdVector *= secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, thirdVector, expected);
    }

    // vec2 * float
    {
        const tabi::vec2 expected(2.5f, -10.0f);
        const float scalar = 2.5f;

        // a * b (float)
        const tabi::vec2 vector(1.0f, -4.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, vector * scalar, expected);

        // a *= b (float)
        tabi::vec2 scaledVector = vector;
        scaledVector *= scalar;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, scaledVector, expected);
    }
}

TEST(Vec2Tests, Division)
{
    // vec2 / vec2
    {
        const tabi::vec2 expected(-2.5f, -156.223f);
        const tabi::vec2 divisor(-3.0f, 1.5f);
        
        // a / b (vec2)
        const tabi::vec2 vector(7.5f, -234.3345f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, vector / divisor, expected);

        // a /= b (vec2)
        tabi::vec2 dividedVector = vector;
        dividedVector /= divisor;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, vector / divisor, expected);
    }

    // vec2 / float
    {
        // a / b (float)
        const tabi::vec2 expected(2.5f, 0.0f);
        const float divisor = 3.0f;

        const tabi::vec2 vector(7.5f, 0.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, vector / divisor, expected);

        // a /= b (float)
        tabi::vec2 dividedVector = vector;
        dividedVector /= divisor;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec2Equal, vector / divisor, expected);
    }
}
