#include "GJK.h"

#include <Colliders/Sphere.h>
#include <Colliders/Box.h>

#include "gtest/gtest.h"

TEST(GJKCollisionTests, SphereOverlap)
{
    const float sphereRadius = 5.0f;

    // Unmoved
    {
        tabi::SphereCollider sc1(sphereRadius);

        tabi::SphereCollider sc2(sphereRadius);

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&sc1, &sc2));
    }

    // Moved
    {
        tabi::SphereCollider sc1(sphereRadius);

        tabi::SphereCollider sc2(sphereRadius);
        sc2.SetWorldPosition(
            tabi::vec3{ 
                sphereRadius / 2.0f, 
                0.0f, 
                0.0f 
            }
        );

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&sc1, &sc2));

        tabi::SphereCollider sc3(sphereRadius);
        sc3.SetWorldPosition(
            tabi::vec3{
                sphereRadius * 2.1f,
                0.0f,
                0.0f
            }
        );

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&sc1, &sc3));
    }

    // Scaled
    {
        tabi::SphereCollider sc1(sphereRadius);

        tabi::SphereCollider sc2(sphereRadius);
        sc2.SetWorldPosition(
            tabi::vec3{
                sphereRadius * 3.0f,
                0.0f,
                0.0f
            }
        );
        sc2.SetWorldScale(
            tabi::vec3{ 
                2.0f, 
                1.0f, 
                1.0f 
            }
        );

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&sc1, &sc2));

        tabi::SphereCollider sc3(sphereRadius);
        sc3.SetWorldPosition(
            tabi::vec3{ 
                sphereRadius * 1.5f,
                sphereRadius * 1.5f,
                sphereRadius * 1.5f
            }
        );
        sc3.SetWorldScale(
            tabi::vec3{ 
                0.4f, 
                0.4f, 
                0.4f 
            }
        );

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&sc1, &sc3));
    }

    // Scaled and rotated
    {
        tabi::SphereCollider sc1(sphereRadius);

        tabi::SphereCollider sc2(sphereRadius);
        sc2.SetWorldPosition(
            tabi::vec3{
                sphereRadius * 3.0f,
                0.0f, 
                0.0f 
            }
        );
        sc2.SetWorldScale(
            tabi::vec3{
                1.0f,
                2.0f,
                1.0f
            }
        );
        sc2.SetWorldRotation(
            tabi::vec3{
                0.0f,
                0.0f,
                1.57079633f
            }
        );

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&sc1, &sc2));

        tabi::SphereCollider sc3(sphereRadius);
        sc3.SetWorldPosition(
            tabi::vec3{
                0.0f,
                0.0f,
                sphereRadius * 2.0f 
            }
        );
        sc3.SetWorldScale(
            tabi::vec3{
                0.4f,
                1.5f,
                1.0f
            }
        );
        sc3.SetWorldRotation(
            tabi::vec3{
                0.0f,
                -1.57079633f,
                0.0f
            }
        );

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&sc1, &sc3));
    }
}

TEST(GJKCollisionTests, BoxOverlap)
{
    const tabi::vec3 halfBoxExtents{0.5f, 0.5f, 0.5f};

    // Unmoved
    {
        tabi::BoxCollider bc1(halfBoxExtents);
        tabi::BoxCollider bc2(halfBoxExtents);

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));
    }

    // Moved
    {
        tabi::BoxCollider bc1(halfBoxExtents);

        tabi::BoxCollider bc2(halfBoxExtents);
        bc2.SetWorldPosition(halfBoxExtents / 2.0f);

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

        tabi::BoxCollider bc3(halfBoxExtents);
        bc3.SetWorldPosition(halfBoxExtents * 2.1f);

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc3));
    }
    
    // Scaled
    {
        tabi::BoxCollider bc1(halfBoxExtents);

        tabi::BoxCollider bc2(halfBoxExtents);
        bc2.SetWorldPosition(halfBoxExtents * 1.8f);
        bc2.SetWorldScale(
            tabi::vec3{
                2.0f,
                2.0f,
                2.0f
            }
        );

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

        tabi::BoxCollider bc3(halfBoxExtents);
        bc3.SetWorldPosition(halfBoxExtents * 1.5f);
        bc3.SetWorldScale(
            tabi::vec3{
                0.4f,
                0.4f,
                0.4f
            }
        );

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc3));
    }

    // Rotated
    {
        tabi::BoxCollider bc1(halfBoxExtents);
        bc1.SetWorldRotation(
            tabi::vec3{
                0.0f,
                0.0f,
                0.785398163f
            }
        );

        {
            tabi::BoxCollider bc2(halfBoxExtents);
            bc2.SetWorldRotation(
                tabi::vec3{
                    0.0f,
                    0.0f,
                    0.785398163f
                }
            );
            
            bc2.SetWorldPosition(
                tabi::vec3{
                    halfBoxExtents.x * 2.0f,
                    0.0f,
                    0.0f
                }
            );
            EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

            bc2.SetWorldPosition(
                tabi::vec3{
                    -halfBoxExtents.x * 2.0f,
                    0.0f,
                    0.0f
                }
            );
            EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

            bc2.SetWorldPosition(
                tabi::vec3{
                    0.0f, 
                    halfBoxExtents.y * 2.0f,
                    0.0f
                }
            );
            EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

            bc2.SetWorldPosition(
                tabi::vec3{
                    0.0f,
                    -halfBoxExtents.y * 2.0f,
                    0.0f
                }
            );
            EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

            bc2.SetWorldPosition(
                tabi::vec3{
                    0.0f,
                    0.0f,
                    halfBoxExtents.z * 2.0f
                }
            );
            EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

            bc2.SetWorldPosition(
                tabi::vec3{
                    0.0f,
                    0.0f,
                    -halfBoxExtents.z * 2.0f
                }
            );
            EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));
        }

        {
            tabi::BoxCollider bc3(halfBoxExtents);
            bc3.SetWorldRotation(
                tabi::vec3{
                    0.0f,
                    0.0f,
                    0.785398163f
                }
            );

            bc3.SetWorldPosition(halfBoxExtents * 1.5f);
            EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc3));

            bc3.SetWorldPosition(
                tabi::vec3{
                    halfBoxExtents.x * -1.5f,
                    halfBoxExtents.y * 1.5f,
                    halfBoxExtents.z * 1.5f
                }
            );
            EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc3));

            bc3.SetWorldPosition(
                tabi::vec3{
                    halfBoxExtents.x * -1.5f,
                    halfBoxExtents.y * -1.5f,
                    halfBoxExtents.z * 1.5f
                }
            );
            EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc3));

            bc3.SetWorldPosition(
                tabi::vec3{
                    halfBoxExtents.x * 1.5f,
                    halfBoxExtents.y * -1.5f,
                    halfBoxExtents.z * 1.5f
                }
            );
            EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc3));
        }
    }

    // Scaled and rotated
    {
        tabi::BoxCollider bc1(halfBoxExtents);

        tabi::BoxCollider bc2(halfBoxExtents);
        bc2.SetWorldPosition(
            tabi::vec3{
                halfBoxExtents.x * 2.5f,
                0.0f,
                0.0f
            }
        );
        bc2.SetWorldScale(
            tabi::vec3{
                1.0f,
                2.0f,
                1.0f
            }
        );
        bc2.SetWorldRotation(
            tabi::vec3{
                0.0f,
                0.0f,
                1.57079633f
            }
        );

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc2));

        tabi::BoxCollider bc3(halfBoxExtents);
        bc3.SetWorldPosition(
            tabi::vec3{
                0.0f,
                0.0f,
                halfBoxExtents.z * 2.0f
            }
        );
        bc3.SetWorldScale(
            tabi::vec3{
                0.4f,
                1.5f,
                1.0f
            }
        );
        bc3.SetWorldRotation(
            tabi::vec3{
                0.0f,
                -1.57079633f,
                0.0f
            }
        );

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &bc3));
    }
}

TEST(GJKCollisionTests, SphereBoxOverlap)
{
    const float sphereRadius = 5.0f;
    const tabi::vec3 halfBoxExtents{ 0.5f, 0.5f, 0.5f };

    // Unmoved
    {
        tabi::SphereCollider sc(sphereRadius);
        tabi::BoxCollider bc(halfBoxExtents);

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc, &sc));
    }

    // Moved
    {
        tabi::SphereCollider sc1(sphereRadius);
        sc1.SetWorldPosition(halfBoxExtents);

        tabi::BoxCollider bc1(halfBoxExtents);

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc1));

        tabi::SphereCollider sc2(sphereRadius);
        sc2.SetWorldPosition(halfBoxExtents + (sphereRadius * 1.1f));

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc2));
    }

    // Scaled
    {
        tabi::SphereCollider sc1(sphereRadius);
        sc1.SetWorldScale(
            tabi::vec3{
                2.0f,
                2.0f,
                2.0f
            }
        );
        sc1.SetWorldPosition(halfBoxExtents + (sphereRadius * 1.1f));

        tabi::BoxCollider bc1(halfBoxExtents);

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc1));

        tabi::SphereCollider sc2(sphereRadius);
        sc2.SetWorldScale(
            tabi::vec3{
                2.0f,
                2.0f,
                2.0f
            }
        );
        sc2.SetWorldPosition(halfBoxExtents + (sphereRadius * 2.1f));

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc2));
    }

    // Rotated
    {
        tabi::SphereCollider sc1(sphereRadius);
        sc1.SetWorldPosition(halfBoxExtents * sphereRadius * 0.8f );

        tabi::BoxCollider bc1(halfBoxExtents);
        bc1.SetWorldRotation(
            tabi::vec3{
                0.0f,
                0.0f,
                0.785398163f
            }
        );

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc1));

        tabi::SphereCollider sc2(sphereRadius);
        sc2.SetWorldPosition(
            tabi::vec3{
                halfBoxExtents.x * sphereRadius * 3.0f, 
                halfBoxExtents.y * sphereRadius * 3.0f, 
                0.0f
            }
        );

        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc2));
    }

    // Scaled and rotated
    {
        tabi::SphereCollider sc1(sphereRadius);
        sc1.SetWorldPosition(
            tabi::vec3{
                sphereRadius * 2.0f,
                0.0f,
                0.0f
            }
        );
        sc1.SetWorldScale(
            tabi::vec3{
                1.0f,
                2.0f,
                1.0f
            }
        );
        sc1.SetWorldRotation(
            tabi::vec3{
                0.0f,
                0.0f,
                1.57079633f
            }
        );

        tabi::BoxCollider bc1(halfBoxExtents);

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc1));

        tabi::SphereCollider sc2(sphereRadius);
        sc2.SetWorldPosition(
            tabi::vec3{
                0.6f * sphereRadius,
                (0.6f * sphereRadius) + halfBoxExtents.y,
                0.0f
            }
        );
        sc2.SetWorldScale(
            tabi::vec3{
                0.5f,
                1.0f,
                1.0f
            }
        );
        sc2.SetWorldRotation(
            tabi::vec3{
                0.0f,
                0.0f,
                0.785398163f
            }
        );

        EXPECT_TRUE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc2));

        bc1.SetWorldRotation(tabi::vec3{ 0.0f, 0.0f, 0.785398163f });
        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc2));

        bc1.SetWorldPosition(tabi::vec3{});
        sc2.SetWorldRotation(
            tabi::vec3{
                0.0f,
                0.0f,
                0.785398163f * 1.5f
            }
        );
        EXPECT_FALSE(tabi::GJK::CollidersAreOverlapping(&bc1, &sc2));
    }
}
