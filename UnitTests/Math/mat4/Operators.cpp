#include "Precidates.h"

#include "Math/mat4.h"
#include "Math/vec3.h"

#include "gtest/gtest.h"

/** Tests for matrix operators */

TEST(Mat4Tests, Addition)
{
    const tabi::mat4 expected(
        1.0f,   -2.0f,  -3.0f, -4.0f,
        5.0f,   -6.0f,  -7.0f, -8.0f,
        9.0f,    10.0f,  11.0f, 12.0f,
        13.0f,   14.0f,  15.0f, 16.0f
    );

    // a + b
    const tabi::mat4 firstMatrix(
         0.0f,  0.5f,  1.0f, 1.5f,
         2.0f,  2.5f,  3.0f, 3.5f,
         4.0f,  4.5f,  5.0f, 5.5f,
        -6.0f, -6.5f, -7.0f, 7.5f
    );

    const tabi::mat4 secondMatrix(
        1.0f,   -2.5f,  -4.0f,  -5.5f,
        3.0f,   -8.5f,  -10.0f, -11.5f,
        5.0f,    5.5f,   6.0f,   6.5f,
        19.0f,   20.5f,  22.0f,  8.5f
    );

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, firstMatrix + secondMatrix, expected);

    // a += b
    tabi::mat4 thirdMatrix = firstMatrix;
    thirdMatrix += secondMatrix;

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, thirdMatrix, expected);
}

TEST(Mat4Tests, Subtraction)
{
    // a - b
    // a -= b

    const tabi::mat4 expected(
        1.0f, -2.0f, -3.0f, -4.0f,
        5.0f, -6.0f, -7.0f, -8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    );

    // a - b
    const tabi::mat4 firstMatrix(
        0.0f, 0.5f, 1.0f, 1.5f,
        2.0f, 2.5f, 3.0f, 3.5f,
        4.0f, 4.5f, 5.0f, 5.5f,
        -6.0f, -6.5f, -7.0f, 7.5f
    );

    const tabi::mat4 secondMatrix(
        -1.0f, 2.5f, 4.0f, 5.5f,
        -3.0f, 8.5f, 10.0f, 11.5f,
        -5.0f, -5.5f, -6.0f, -6.5f,
        -19.0f, -20.5f, -22.0f, -8.5f
    );

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, firstMatrix - secondMatrix, expected);

    // a -= b
    tabi::mat4 thirdMatrix = firstMatrix;
    thirdMatrix -= secondMatrix;

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, thirdMatrix, expected);
}

TEST(Mat4Tests, Multiplication)
{
    // a * b (mat4)
    // a *= b (mat4)
    {
        const tabi::mat4 expected(
            -124.0f, 100.0f, 60.0f, 20.0f,
            -292.0f, 268.0f, 164.0f, 60.0f,
            -460.0f, 436.0f, 268.0f, 100.0f,
            420.0f, -460.0f, -292.0f, -124.0f
        );

        const tabi::mat4 firstMatrix(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            -13.0f, -14.0f, -15.0f, 0.0f
        );

        const tabi::mat4 secondMatrix(
            0.0f, 12.0f, 8.0f, 4.0f,
            -15.0f, 11.0f, 7.0f, 3.0f,
            -14.0f, 10.0f, 6.0f, 2.0f,
            -13.0f, 9.0f, 5.0f, 1.0f
        );

        EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, firstMatrix * secondMatrix, expected);
        EXPECT_FALSE(secondMatrix * firstMatrix == expected);

        tabi::mat4 thirdMatrix = firstMatrix;
        thirdMatrix *= secondMatrix;

        EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, thirdMatrix, expected);
    }


    // a * b (vec3)
    {
        const tabi::vec3 expected(1340.7f / -6735.5f, 3144.3f / -6735.5f, 4947.9f / -6735.5f);

        const tabi::mat4 matrix(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            -13.0f, -14.0f, -15.0f, 0.0f
        );

        const tabi::vec3 vector(7.5f, -2.0f, 444.4f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, matrix * vector, expected);
    }

    // a * b (vec4)
    {
        const tabi::vec4 expected(1576.7f, 3616.3f, 5655.9f, -6735.5f);

        const tabi::mat4 matrix(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            -13.0f, -14.0f, -15.0f, 0.0f
        );

        const tabi::vec4 vector(7.5f, -2.0f, 444.4f, 60.0f);

        EXPECT_PRED_FORMAT2(MathPredicates::Vec4Equal, matrix * vector, expected);
    }

    // a * b (float)
    // a *= b (float)
    {
        const tabi::mat4 expected(
            2.0f, 4.0f, 6.0f, 8.0f,
            10.0f, 12.0f, 14.0f, 16.0f,
            18.0f, 20.0f, 22.0f, 24.0f,
            -26.0f, -28.0f, -30.0f, 0.0f
        );

        const float scalar = 2.0f;

        const tabi::mat4 firstMatrix(
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            -13.0f, -14.0f, -15.0f, 0.0f
        );

        EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, firstMatrix * scalar, expected);

        tabi::mat4 secondMatrix = firstMatrix;
        secondMatrix *= scalar;

        EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, secondMatrix, expected);
    }
}
