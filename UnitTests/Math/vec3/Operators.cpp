#include "Precidates.h"

#include "Math/vec3.h"

#include "gtest/gtest.h"

/** Tests for vector operators */

TEST(Vec3Tests, Addition)
{
    // vec3 + vec3
    {
        const tabi::vec3 expected(5.0f, -7.0f, 1685.0f);

        // a + b
        const tabi::vec3 firstVector(1.0f, 7.0f, 685.0f);
        const tabi::vec3 secondVector(4.0f, -14.0f, 1000.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, firstVector + secondVector, expected);

        // a += b
        tabi::vec3 thirdVector = firstVector;
        thirdVector += secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, thirdVector, expected);
    }

    // vec3 + float
    {
        const tabi::vec3 expected(5.0f, -7.0f, 1685.0f);

        // a + b
        const tabi::vec3 firstVector(0.0f, -12.0f, 1680.0f);
        const float addedValue = 5.0f;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, firstVector + addedValue, expected);

        // a += b
        tabi::vec3 secondVector = firstVector;
        secondVector += addedValue;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, secondVector, expected);
    }
}

TEST(Vec3Tests, Subtraction)
{
    // vec3 - vec3
    {
        const tabi::vec3 expected(-3.0f, 21.0f, -315.0f);

        // a - b
        const tabi::vec3 firstVector(1.0f, 7.0f, 685.0f);
        const tabi::vec3 secondVector(4.0f, -14.0f, 1000.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, firstVector - secondVector, expected);

        // a -= b
        tabi::vec3 thirdVector = firstVector;
        thirdVector -= secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, thirdVector, expected);
    }

    // vec3 - float
    {
        const tabi::vec3 expected(-3.0f, 11.0f, 1675.0f);

        // a - b
        const tabi::vec3 firstVector(2.0f, 16.0f, 1680.0f);
        const float subtractedValue = 5.0f;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, firstVector - subtractedValue, expected);

        // a -= b
        tabi::vec3 secondVector = firstVector;
        secondVector -= subtractedValue;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, secondVector, expected);
    }
}

TEST(Vec3Tests, Multiplication)
{
    // vec3 * vec3
    {
        const tabi::vec3 expected(2.5f, -10.0f, 66.6f);

        // a * b (vec3)
        const tabi::vec3 firstVector(2.5f, 20.0f, 33.3f);
        const tabi::vec3 secondVector(1.0f, -0.5f, 2.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, firstVector * secondVector, expected);

        // a *= b (vec3)
        tabi::vec3 thirdVector = firstVector;
        thirdVector *= secondVector;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, thirdVector, expected);
    }

    // vec3 * float
    {
        const tabi::vec3 expected(2.5f, -10.0f, 66.6f);
        const float scalar = 2.5f;

        // a * b (float)
        const tabi::vec3 vector(1.0f, -4.0f, 26.64f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, vector * scalar, expected);

        // a *= b (float)
        tabi::vec3 scaledVector = vector;
        scaledVector *= scalar;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, scaledVector, expected);
    }
}

TEST(Vec3Tests, Division)
{
    // vec3 / vec3
    {
        const tabi::vec3 expected(-2.5f, 0.0f, -156.223f);
        const tabi::vec3 divisor(-3.0f, 6.0f, 1.5f);
        
        // a / b (vec3)
        const tabi::vec3 vector(7.5f, 0.0f, -234.3345f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, vector / divisor, expected);

        // a /= b (vec3)
        tabi::vec3 dividedVector = vector;
        dividedVector /= divisor;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, vector / divisor, expected);
    }

    // vec3 / float
    {
        // a / b (float)
        const tabi::vec3 expected(2.5f, 0.0f, -156.223f);
        const float divisor = 3.0f;

        const tabi::vec3 vector(7.5f, 0.0f, -468.669f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, vector / divisor, expected);

        // a /= b (float)
        tabi::vec3 dividedVector = vector;
        dividedVector /= divisor;

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, vector / divisor, expected);
    }
}
