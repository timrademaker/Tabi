#include "gtest/gtest.h"

#include "Math/mat4.h"
#include "Math/vec3.h"

/** Tests for matrix translation */

TEST(Mat4Tests, Translate)
{
    const tabi::vec3 translation(10.0f, 15.0f, -20.0f);

    tabi::mat4 translatedMatrix;
    translatedMatrix.Translate(translation);

    const tabi::vec3 outTranslation = translatedMatrix.GetPosition();
    
    EXPECT_EQ(outTranslation, translation);

    // Translate the matrix again
    translatedMatrix.Translate(translation);
    const tabi::vec3 outDoubleTranslation = translatedMatrix.GetPosition();

    EXPECT_EQ(outDoubleTranslation, translation + translation);

    // Forcibly set the translation
    const tabi::vec3 forcedPosition(-50.0f, 66.0f, 12.3f);
    translatedMatrix.SetPosition(forcedPosition);

    const tabi::vec3 outForcedPosition = translatedMatrix.GetPosition();

    EXPECT_EQ(outForcedPosition, forcedPosition);
}

TEST(Mat4Tests, StaticTranslate)
{
    const tabi::vec3 translation(10.0f, 15.0f, -20.0f);

    const tabi::mat4 identity = tabi::mat4::Identity();
    const tabi::mat4 translatedMatrix = tabi::mat4::Translate(identity, translation);

    const tabi::vec3 outTranslation = translatedMatrix.GetPosition();

    EXPECT_EQ(outTranslation, translation);

    // Translate the matrix again
    const tabi::mat4 doubleTranslatedMatrix = tabi::mat4::Translate(translatedMatrix, translation);
    
    const tabi::vec3 outDoubleTranslation = doubleTranslatedMatrix.GetPosition();

    EXPECT_EQ(outDoubleTranslation, translation + translation);

    // Forcibly set the translation
    const tabi::vec3 forcedPosition(-50.0f, 66.0f, 12.3f);

    tabi::mat4 forciblyMovedMatrix = tabi::mat4::SetPosition(doubleTranslatedMatrix, forcedPosition);

    const tabi::vec3 outForcedPosition = forciblyMovedMatrix.GetPosition();

    EXPECT_EQ(outForcedPosition, forcedPosition);
}
