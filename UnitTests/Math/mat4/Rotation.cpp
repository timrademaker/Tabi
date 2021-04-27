#include "Precidates.h"

#include "Math/mat4.h"
#include "Math/vec3.h"

#include "gtest/gtest.h"

/** Tests for matrix rotation */

TEST(Mat4Tests, Rotation)
{
	// X
	{
		// Rotate once
		const tabi::mat4 expectedMatRotX(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2836622f, -0.9589243f, 0.0f,
			0.0f, 0.9589243f, 0.2836622f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		tabi::mat4 outMatRotX = tabi::mat4::Identity();
		outMatRotX.RotateX(5.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotX, expectedMatRotX);

		// Rotate again
		const tabi::mat4 expectedMatDoubleRotX(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -0.4161468f, 0.9092974f, 0.0f,
			0.0f, -0.9092974f, -0.4161468f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		tabi::mat4 outMatDoubleRotX = outMatRotX;
		outMatDoubleRotX.RotateX(-3.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatDoubleRotX, expectedMatDoubleRotX);
		
		// Rotate back to no rotation
		tabi::mat4 outMatRotBackX = outMatDoubleRotX;
		outMatRotBackX.RotateX(-2.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotBackX, tabi::mat4::Identity());
	}

	// Y
	{
		// Rotate once
		const tabi::mat4 expectedMatRotY(
			-0.8011436f, 0.0f, -0.5984721f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.5984721f, 0.0f, -0.8011436f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		tabi::mat4 outMatRotY = tabi::mat4::Identity();
		outMatRotY.RotateY(2.5f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotY, expectedMatRotY);

		// Rotate again
		const tabi::mat4 expectedMatDoubleRotY(
			0.5403023f, 0.0f, -0.8414710f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.8414710f, 0.0f, 0.5403023f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		tabi::mat4 outMatDoubleRotY = outMatRotY;
		outMatDoubleRotY.RotateY(-1.5f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatDoubleRotY, expectedMatDoubleRotY);

		// Rotate back to no rotation
		tabi::mat4 outMatRotBackY = outMatDoubleRotY;
		outMatRotBackY.RotateY(-1.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotBackY, tabi::mat4::Identity());
	}

	// Z
	{
		const tabi::mat4 expectedMatRotZ(
			0.5403023f, 0.8414710f, 0.0f, 0.0f,
			-0.8414710f, 0.5403023f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		tabi::mat4 outMatRotZ = tabi::mat4::Identity();
		outMatRotZ.RotateZ(1.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotZ, expectedMatRotZ);

		// Rotate again
		const tabi::mat4 expectedMatDoubleRotZ(
			0.9689124f, 0.2474040f, 0.0f, 0.0f,
			-0.2474040f, 0.9689124f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		tabi::mat4 outMatDoubleRotZ = outMatRotZ;
		outMatDoubleRotZ.RotateZ(-0.75f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatDoubleRotZ, expectedMatDoubleRotZ);

		// Rotate back to no rotation
		tabi::mat4 outMatRotBackZ = outMatDoubleRotZ;
		outMatRotBackZ.RotateZ(-0.25f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotBackZ, tabi::mat4::Identity());
	}
	
	// XY
	{
		const tabi::mat4 expectedMatRotXY(
			-0.4161468f, 0.7651474f, -0.4912955f, 0.0f,
			0.0f, 0.5403023f, 0.8414710f, 0.0f,
			0.9092974f, 0.3501755f, -0.2248451f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		tabi::mat4 outMatRotXY = tabi::mat4::Identity();
		outMatRotXY.RotateX(1.0f);
		outMatRotXY.RotateY(2.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotXY, expectedMatRotXY);

		// Rotate back
		tabi::mat4 outMatRotBackXY = outMatRotXY;
		outMatRotBackXY.RotateY(-2.0f);
		outMatRotBackXY.RotateX(-1.0f);
		
		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotBackXY, tabi::mat4::Identity());
	}

	// XZ
	{
		const tabi::mat4 expectedMatRotXZ(
			0.0707372f, 0.0705600f, 0.9949962f, 0.0f,
			-0.9974950f, 0.0050038f, 0.0705600f, 0.0f,
			-0.0f, -0.9974950f, 0.0707372f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		tabi::mat4 outMatRotXZ = tabi::mat4::Identity();
		outMatRotXZ.RotateX(1.5f);
		outMatRotXZ.RotateZ(1.5f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotXZ, expectedMatRotXZ);

		// Rotate back
		tabi::mat4 outMatRotBackXZ = outMatRotXZ;
		outMatRotBackXZ.RotateZ(-1.5f);
		outMatRotBackXZ.RotateX(-1.5f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotBackXZ, tabi::mat4::Identity());
	}

	// YZ
	{
		const tabi::mat4 expectedMatRotYZ(
			0.1119695f, 0.9839860f, 0.1386885f, 0.0f,
			0.6181140f, -0.1782461f, 0.7656131f, 0.0f,
			0.7780732f, -0.0f, -0.6281736f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		tabi::mat4 outMatRotYZ = tabi::mat4::Identity();
		outMatRotYZ.RotateY(2.25f);
		outMatRotYZ.RotateZ(1.75f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotYZ, expectedMatRotYZ);

		// Rotate back
		tabi::mat4 outMatRotBackYZ = outMatRotYZ;
		outMatRotBackYZ.RotateZ(-1.75f);
		outMatRotBackYZ.RotateY(-2.25f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotBackYZ, tabi::mat4::Identity());
	}

	// XYZ
	{
		const tabi::mat4 expectedMatRotXYZ(
			0.4119822f, -0.6812427f, 0.6051273f, 0.0f,
			0.0587266f, -0.6428728f, -0.7637183f, 0.0f,
			0.9092974f, 0.3501755f, -0.2248451f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		tabi::mat4 outMatRotXYZ = tabi::mat4::Identity();
		outMatRotXYZ.RotateX(1.0f);
		outMatRotXYZ.RotateY(2.0f);
		outMatRotXYZ.RotateZ(3.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotXYZ, expectedMatRotXYZ);

		// Rotate back
		tabi::mat4 outMatRotBackXYZ = outMatRotXYZ;

		outMatRotBackXYZ.RotateZ(-3.0f);
		outMatRotBackXYZ.RotateY(-2.0f);
		outMatRotBackXYZ.RotateX(-1.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotBackXYZ, tabi::mat4::Identity());
	}
}

TEST(Mat4Tests, RotationStatic)
{
	const tabi::mat4 identity = tabi::mat4::Identity();

	// X
	{
		const tabi::mat4 expectedMatRotX(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.2836622f, -0.9589243f, 0.0f,
			0.0f, 0.9589243f, 0.2836622f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		const tabi::mat4 outMatRotX = tabi::mat4::RotateX(identity, 5.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotX, expectedMatRotX);
	}

	// Y
	{
		const tabi::mat4 expectedMatRotY(
			-0.8011436f, 0.0f, -0.5984721f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.5984721f, 0.0f, -0.8011436f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		const tabi::mat4 outMatRotY = tabi::mat4::RotateY(identity, 2.5f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotY, expectedMatRotY);
	}

	// Z
	{
		const tabi::mat4 expectedMatRotZ(
			0.5403023f, 0.8414710f, 0.0f, 0.0f,
			-0.8414710f, 0.5403023f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		const tabi::mat4 outMatRotZ = tabi::mat4::RotateZ(identity, 1.0f);

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatRotZ, expectedMatRotZ);
	}
}

TEST(Mat4Tests, InverseRotation)
{
	// X
	{
		const float xRot = 5.0f;

		const tabi::mat4 expectedMatUnRotateX = tabi::mat4::RotateX(tabi::mat4::Identity(), -xRot);

		tabi::mat4 outMatUnRotateX = tabi::mat4::Identity();
		outMatUnRotateX.SetInverseRotation(tabi::vec3{ xRot, 0.0f, 0.0f });

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatUnRotateX, expectedMatUnRotateX);
	}
	// Y
	{
		const float yRot = 2.5f;

		const tabi::mat4 expectedMatUnRotateY = tabi::mat4::RotateY(tabi::mat4::Identity(), -yRot);

		tabi::mat4 outMatUnRotateY = tabi::mat4::Identity();
		outMatUnRotateY.SetInverseRotation(tabi::vec3{ 0.0f, yRot, 0.0f });

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatUnRotateY, expectedMatUnRotateY);
	}

	// Z
	{
		const float zRot = 1.0f;

		const tabi::mat4 expectedMatUnRotateZ = tabi::mat4::RotateZ(tabi::mat4::Identity(), -zRot);

		tabi::mat4 outMatUnRotateZ = tabi::mat4::Identity();
		outMatUnRotateZ.SetInverseRotation(tabi::vec3{ 0.0f, 0.0f, zRot });

		EXPECT_PRED_FORMAT2(MathPredicates::Mat4Equal, outMatUnRotateZ, expectedMatUnRotateZ);
	}

	// XY
	{
		// Rotate a vector, then rotate it back
		const tabi::vec3 rotation{ 0.12f, -1.247f, 0.0f };

		// 1-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.0f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 2-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 3-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, -1.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}
	}

	// XZ
	{
		// Rotate a vector, then rotate it back
		const tabi::vec3 rotation{ 0.12f, 0.0f, -2.127f };

		// 1-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.0f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 2-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 3-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, -1.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}
	}

	// YZ
	{
		// Rotate a vector, then rotate it back
		const tabi::vec3 rotation{ 0.0f, 2.48f, -3.14f };

		// 1-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.0f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 2-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 3-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, -1.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}
	}

	// XYZ
	{
		// Rotate a vector, then rotate it back
		const tabi::vec3 rotation{ 1.0f, 1.36f, 1.57f };

		// 1-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.0f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 2-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, 0.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}

		// 3-axis direction vector
		{
			const tabi::vec3 startVector{ 1.0f, 0.5f, -1.0f };

			const tabi::vec3 rotatedVector = tabi::mat4::SetRotation(tabi::mat4::Identity(), rotation) * startVector;
			const tabi::vec3 unrotatedVector = tabi::mat4::SetInverseRotation(tabi::mat4::Identity(), rotation) * rotatedVector;

			EXPECT_PRED_FORMAT2(MathPredicates::Vec3Equal, unrotatedVector, startVector);
		}
	}
}
