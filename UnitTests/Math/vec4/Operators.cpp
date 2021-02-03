#include "Precidates.h"

#include "Math/vec4.h"

#include "gtest/gtest.h"

/** Tests for vector operators */
TEST(Vec4Tests, Addition)
{
    // vec4 + vec4
    {
        const tabi::vec4 expected(5.0f, -7.0f, 1685.0f, 85.75f);

        // a + b
        const tabi::vec4 firstVector(1.0f, 7.0f, 685.0f, 21.05f);
        const tabi::vec4 secondVector(4.0f, -14.0f, 1000.0f, 64.7f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, (firstVector + secondVector), expected);

        // a += b
        tabi::vec4 thirdVector = firstVector;
        thirdVector += secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, thirdVector, expected);
    }

    // vec4 + float
    {
        const tabi::vec4 expected(5.0f, -7.0f, 1685.0f, 85.75f);

        // a + b
        const tabi::vec4 firstVector(0.0f, -12.0f, 1680.0f, 80.75f);
        const float addedValue = 5.0f;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, (firstVector + addedValue), expected);

        // a += b
        tabi::vec4 secondVector = firstVector;
        secondVector += addedValue;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, secondVector, expected);
    }
}

TEST(Vec4Tests, Subtraction)
{
    // vec4 - vec4
    {
        const tabi::vec4 expected(-3.0f, 21.0f, -315.0f, 123.4f);

        // a - b
        const tabi::vec4 firstVector(1.0f, 7.0f, 685.0f, 136.8f);
        const tabi::vec4 secondVector(4.0f, -14.0f, 1000.0f, 13.4f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, (firstVector - secondVector), expected);

        // a -= b
        tabi::vec4 thirdVector = firstVector;
        thirdVector -= secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, thirdVector, expected);
    }

    // vec4 - float
    {
        const tabi::vec4 expected(-3.0f, 11.0f, 1675.0f, 18.66f);

        // a - b
        const tabi::vec4 firstVector(2.0f, 16.0f, 1680.0f, 23.66f);
        const float subtractedValue = 5.0f;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, (firstVector - subtractedValue), expected);

        // a -= b
        tabi::vec4 secondVector = firstVector;
        secondVector -= subtractedValue;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, secondVector, expected);
    }
}

TEST(Vec4Tests, Multiplication)
{
    // vec4 * vec4
    {
        const tabi::vec4 expected(2.5f, -10.0f, 66.6f, 0.225f);

        // a * b (vec4)
        const tabi::vec4 firstVector(2.5f, 20.0f, 33.3f, 0.3f);
        const tabi::vec4 secondVector(1.0f, -0.5f, 2.0f, 0.75f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, (firstVector * secondVector), expected);

        // a *= b (vec4)
        tabi::vec4 thirdVector = firstVector;
        thirdVector *= secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, thirdVector, expected);
    }

    // vec4 * float
    {
        const tabi::vec4 expected(2.5f, -10.0f, 66.6f, 0.2f);
        const float scalar = 2.5f;

        // a * b (float)
        const tabi::vec4 vector(1.0f, -4.0f, 26.64f, 0.08f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, (vector * scalar), expected);

        // a *= b (float)
        tabi::vec4 scaledVector = vector;
        scaledVector *= scalar;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, scaledVector, expected);
    }
}

TEST(Vec4Tests, Division)
{
    // vec4 / vec4
    {
        const tabi::vec4 expected(-2.5f, 0.0f, -156.223f, 18.2f);
        const tabi::vec4 divisor(-3.0f, 6.0f, 1.5f, 0.5f);
        
        // a / b (vec4)
        const tabi::vec4 vector(7.5f, 0.0f, -234.3345f, 9.1f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, vector / divisor, expected);

        // a /= b (vec4)
        tabi::vec4 dividedVector = vector;
        dividedVector /= divisor;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, vector / divisor, expected);
    }

    // vec4 / float
    {
        // a / b (float)
        const tabi::vec4 expected(2.5f, 0.0f, -156.223f, 60.2f);
        const float divisor = 3.0f;

        const tabi::vec4 vector(7.5f, 0.0f, -468.669f, 180.6f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, vector / divisor, expected);

        // a /= b (float)
        tabi::vec4 dividedVector = vector;
        dividedVector /= divisor;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, vector / divisor, expected);
    }
}
