#include "Precidates.h"

#include "Math/mat4.h"
#include "Math/vec3.h"

#include "gtest/gtest.h"

#include <numeric>

/** Tests for various matrix functions that don't fit any other category */

TEST(Mat4Tests, Transpose)
{
    tabi::mat4 startMatrix;
    tabi::mat4 expectedMatrix;

    float i = 0.0f;
    for (int a = 0; a < 4; ++a)
    {
        for (int b = 0; b < 4; ++b)
        {
            startMatrix.m[a][b] = i;
            expectedMatrix.m[b][a] = i;

            i += 1.0f;
        }
    }

    tabi::mat4 outcome = startMatrix.Transpose();

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outcome, expectedMatrix);
}

TEST(Mat4Tests, Identity)
{
    const tabi::mat4 tabiIdentity = tabi::mat4::Identity();

    tabi::mat4 identity;
    identity.m[0][0] = 1.0f;
    identity.m[1][1] = 1.0f;
    identity.m[2][2] = 1.0f;
    identity.m[3][3] = 1.0f;

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, identity, tabiIdentity);
}

TEST(Mat4Tests, LookAt)
{
    const tabi::mat4 expectedLookAt{
        1.0f,  0.0f,          0.0f,         -0.0f,
        0.0f,  0.980580688f, -0.196116135f,  0.0f,
        0.0f,  0.196116135f,  0.980580688f, 0.0f,
        0.0f,  -2.74562597f, -3.53009057f,   1.0f
    };

    const tabi::mat4 calculatedLookAt = tabi::mat4::CreateLookAtMatrix(tabi::vec3(0.0f, 2.0f, 4.0f), tabi::vec3(0.0f, 3.0f, -1.0f), tabi::vec3(0.0f, 1.0f, 0.0f));

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, calculatedLookAt, expectedLookAt);
}

TEST(Mat4Tests, Projection)
{
    const float degToRad = 3.141592653589793238462643383279502884f / 180.0f;

    const tabi::mat4 expectedProjection{
        1.29903805f, 0.0f,         0.0f,         0.0f,
        0.0f,        1.73205090f,  0.0f,         0.0f,
        0.0f,        0.0f,        -1.00200200f, -1.0f,
        0.0f,        0.0f,        -0.200200200f,  0.0f
    };

    const tabi::mat4 calculatedProjection = tabi::mat4::CreatePerspectiveProjectionMatrix(60.0f * degToRad, 4.0f / 3.0f, 0.1f, 100.0f);

    EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, calculatedProjection, expectedProjection);
}

TEST(Mat4Tests, Forward)
{
    const tabi::mat4 identity = tabi::mat4::Identity();

    const tabi::vec3 outForward = identity.GetForward();
    const tabi::vec3 expectedForward(0.0f, 0.0f, -1.0f);

    EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outForward, expectedForward);

    // Check rotated matrix right
    tabi::mat4 rotatedMatrix = tabi::mat4::Identity();
    // Rotate by 90°
    rotatedMatrix.RotateX(1.57079633f);

    const tabi::vec3 outRotatedForward = rotatedMatrix.GetForward();
    const tabi::vec3 expectedRotatedForward(0.0f, -1.0f, 0.0f);

    EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outRotatedForward, expectedRotatedForward);
}

TEST(Mat4Tests, Right)
{
    const tabi::mat4 identity = tabi::mat4::Identity();

    const tabi::vec3 outRight = identity.GetRight();
    const tabi::vec3 expectedRight(-1.0f, 0.0f, 0.0f);

    EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outRight, expectedRight);

    // Check rotated matrix right
    tabi::mat4 rotatedMatrix = tabi::mat4::Identity();
    // Rotate by 90°
    rotatedMatrix.RotateY(1.57079633f);

    const tabi::vec3 outRotatedRight = rotatedMatrix.GetRight();
    const tabi::vec3 expectedRotatedRight(0.0f, 0.0f, -1.0f);

    EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outRotatedRight, expectedRotatedRight);
}

TEST(Mat4Tests, Up)
{
    // Check identity matrix up
    const tabi::mat4 identity = tabi::mat4::Identity();

    const tabi::vec3 outUp = identity.GetUp();
    const tabi::vec3 expectedUp(0.0f, -1.0f, 0.0f);

    EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outUp, expectedUp);

    // Check rotated matrix up
    tabi::mat4 rotatedMatrix = tabi::mat4::Identity();
    // Rotate by 90°
    rotatedMatrix.RotateX(1.57079633f);

    const tabi::vec3 outRotatedUp = rotatedMatrix.GetUp();
    const tabi::vec3 expectedRotatedUp(0.0f, 0.0f, 1.0f);

    EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, outRotatedUp, expectedRotatedUp);
}
