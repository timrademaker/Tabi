#include "gtest/gtest.h"

#include "Math/mat4.h"

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

    EXPECT_EQ(outcome, expectedMatrix);
}

TEST(Mat4Tests, Identity)
{
    const tabi::mat4 tabiIdentity = tabi::mat4::Identity();

    tabi::mat4 identity;
    identity.m[0][0] = 1.0f;
    identity.m[1][1] = 1.0f;
    identity.m[2][2] = 1.0f;
    identity.m[3][3] = 1.0f;

    EXPECT_EQ(tabiIdentity, identity);
}

TEST(Mat4Tests, LookAt)
{

}

TEST(Mat4Tests, Forward)
{

}

TEST(Mat4Tests, Right)
{

}

TEST(Mat4Tests, Up)
{

}
