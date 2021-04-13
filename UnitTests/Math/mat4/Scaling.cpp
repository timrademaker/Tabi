#include "gtest/gtest.h"

#include "Math/mat4.h"
#include "Math/vec3.h"

/** Tests for matrix scaling */

TEST(Mat4Tests, Scale)
{
    const float scale = 5.0f;

    tabi::mat4 scaledMatrix = tabi::mat4::Identity();
    scaledMatrix.Scale(scale);

    const tabi::vec3 outScale = scaledMatrix.GetScale();

    ASSERT_EQ(outScale.x, scale);
    ASSERT_EQ(outScale.y, scale);
    ASSERT_EQ(outScale.z, scale);

    // Scale the matrix again
    scaledMatrix.Scale(scale);
    
    const tabi::vec3 outDoubleScale = scaledMatrix.GetScale();

    EXPECT_EQ(outDoubleScale.x, scale * scale);
    EXPECT_EQ(outDoubleScale.y, scale * scale);
    EXPECT_EQ(outDoubleScale.z, scale * scale);

    // Forcibly set the scale
    const tabi::vec3 forcedScale(2.0f, 2.0f, 2.0f);
    scaledMatrix.SetScale(forcedScale);
    
    const tabi::vec3 outForcedScale = scaledMatrix.GetScale();

    EXPECT_EQ(outForcedScale, forcedScale);
}

TEST(Mat4Tests, ScaleStatic)
{
    const float scale = 5.0f;

    const tabi::mat4 identity = tabi::mat4::Identity();
    const tabi::mat4 scaledMatrix = tabi::mat4::Scale(identity, scale);

    tabi::vec3 outScale = scaledMatrix.GetScale();

    ASSERT_EQ(outScale.x, scale);
    ASSERT_EQ(outScale.y, scale);
    ASSERT_EQ(outScale.z, scale);

    // Scale the matrix again
    const tabi::mat4 doubleScaledMatrix = tabi::mat4::Scale(scaledMatrix, scale);

    const tabi::vec3 outDoubleScale = doubleScaledMatrix.GetScale();

    EXPECT_EQ(outDoubleScale.x, scale * scale);
    EXPECT_EQ(outDoubleScale.y, scale * scale);
    EXPECT_EQ(outDoubleScale.z, scale * scale);

    // Forcibly set the scale
    const tabi::vec3 forcedScale(2.0f, 2.0f, 2.0f);
    tabi::mat4 forciblyScaledMatrix = tabi::mat4::SetScale(doubleScaledMatrix, forcedScale);

    const tabi::vec3 outForcedScale = forciblyScaledMatrix.GetScale();

    EXPECT_EQ(outForcedScale, forcedScale);
}
