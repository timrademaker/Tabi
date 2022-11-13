#include "MockCollisionCallbackObject.h"
#include "CollisionMatchers.h"

#include <ECS.h>
#include <Components/Transform.h>

#include <Colliders/Sphere.h>
#include <ECS/ColliderComponent.h>
#include <ECS/CollisionSystem.h>

#include "gtest/gtest.h"

class CollisionSystemTests : public ::testing::Test
{

protected:
    CollisionSystemTests()
    {
        // Register collision system
        m_ECS.RegisterSystem<tabi::CollisionSystem>();

        // Create two entities
        CreateEntityWithCollider(m_Entity1, m_Collider1, m_CollisionCallback1);
        CreateEntityWithCollider(m_Entity2, m_Collider2, m_CollisionCallback2);
    }

    void CreateEntityWithCollider(tabi::Entity& a_Entity, tabi::ColliderComponent& a_Collider, MockCollisionCallbackObject& a_CallbackObject)
    {
        a_Entity = m_ECS.CreateEntity();
        m_ECS.AddComponent<tabi::Transform>(a_Entity, {});

        a_Collider.m_Collider = tabi::make_shared<tabi::SphereCollider>(s_SphereRadius);

        a_Collider.m_OnColliderBeginOverlap.Subscribe(&a_CallbackObject, &MockCollisionCallbackObject::OnOverlapBegin);
        a_Collider.m_OnColliderEndOverlap.Subscribe(&a_CallbackObject, &MockCollisionCallbackObject::OnOverlapEnd);

        m_ECS.AddComponent<tabi::ColliderComponent>(a_Entity, a_Collider);
    }

protected:
    tabi::ECS m_ECS;

    tabi::Entity m_Entity1;
    tabi::Entity m_Entity2;

    tabi::ColliderComponent m_Collider1;
    tabi::ColliderComponent m_Collider2;

    MockCollisionCallbackObject m_CollisionCallback1;
    MockCollisionCallbackObject m_CollisionCallback2;

    static constexpr float s_SphereRadius = 0.5f;
};

TEST_F(CollisionSystemTests, OverlapStartEventCalled)
{
    // Set expectations for entity 1
    EXPECT_CALL(m_CollisionCallback1, OnOverlapBegin(::testing::_)).Times(1);

    // Set expectations for entity 2
    EXPECT_CALL(m_CollisionCallback2, OnOverlapBegin(::testing::_)).Times(1);


    // Execute
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };

    m_ECS.Update(1.0f);
}

TEST_F(CollisionSystemTests, OverlapStartEventCalledOnce)
{
    // 1. Have 2 colliders overlap
    // 2. Move one collider (still overlapping with the other collider)
    // 3. Repeat step 2

    // Set expectations for entity 1
    EXPECT_CALL(m_CollisionCallback1, OnOverlapBegin(::testing::_)).Times(1);
    EXPECT_CALL(m_CollisionCallback1, OnOverlapEnd(::testing::_)).Times(0);

    // Set expectations for entity 2
    EXPECT_CALL(m_CollisionCallback2, OnOverlapBegin(::testing::_)).Times(1);
    EXPECT_CALL(m_CollisionCallback2, OnOverlapEnd(::testing::_)).Times(0);


    // Execute
    // Make entities overlap
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    m_ECS.Update(1.0f);

    constexpr size_t moveIterations = 10;
    for (int i = 0; i < moveIterations; ++i)
    {
        // Still overlapping
        m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ (s_SphereRadius / (moveIterations * 2)) * i, 0.0f, 0.0f };

        m_ECS.Update(1.0f);
    }
}

TEST_F(CollisionSystemTests, OverlapStartEventArgument)
{
    // Set expectations for entity 1
    tabi::OverlapInfo overlapInfo1;
    overlapInfo1.m_OtherEntity = m_Entity2;
    overlapInfo1.m_OverlappedCollider = m_Collider2.m_Collider;

    EXPECT_CALL(m_CollisionCallback1, OnOverlapBegin(OverlapInfoMatcher(overlapInfo1))).Times(1);

    // Set expectations for entity 2
    tabi::OverlapInfo overlapInfo2;
    overlapInfo2.m_OtherEntity = m_Entity1;
    overlapInfo2.m_OverlappedCollider = m_Collider1.m_Collider;
    EXPECT_CALL(m_CollisionCallback2, OnOverlapBegin(OverlapInfoMatcher(overlapInfo2))).Times(1);


    // Execute
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };

    m_ECS.Update(1.0f);
}

TEST_F(CollisionSystemTests, OverlapEndEventCalled)
{
    // Set expectations for entity 1
    EXPECT_CALL(m_CollisionCallback1, OnOverlapEnd(::testing::_)).Times(1);

    // Set expectations for entity 2
    EXPECT_CALL(m_CollisionCallback2, OnOverlapEnd(::testing::_)).Times(1);


    // Execute
    // Make entities overlap
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };

    // Make sure entities are registered as overlapping
    m_ECS.Update(1.0f);

    // Stop overlap
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 100.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ -100.0f, 0.0f, 0.0f };

    m_ECS.Update(1.0f);
}

TEST_F(CollisionSystemTests, OverlapEndEventArguments)
{
    // Set expectations for entity 1
    tabi::OverlapInfo overlapInfo1;
    overlapInfo1.m_OtherEntity = m_Entity2;
    overlapInfo1.m_OverlappedCollider = m_Collider2.m_Collider;

    EXPECT_CALL(m_CollisionCallback1, OnOverlapEnd(OverlapInfoMatcher(overlapInfo1))).Times(1);

    // Set expectations for entity 2
    tabi::OverlapInfo overlapInfo2;
    overlapInfo2.m_OtherEntity = m_Entity1;
    overlapInfo2.m_OverlappedCollider = m_Collider1.m_Collider;
    EXPECT_CALL(m_CollisionCallback2, OnOverlapEnd(OverlapInfoMatcher(overlapInfo2))).Times(1);


    // Execute
    // Make entities overlap
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };

    // Make sure entities are registered as overlapping
    m_ECS.Update(1.0f);

    // Stop overlap
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 100.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ -100.0f, 0.0f, 0.0f };

    m_ECS.Update(1.0f);
}

TEST_F(CollisionSystemTests, NoSelfOverlapEvent)
{
    // Set expectations for entity 1
    EXPECT_CALL(m_CollisionCallback1, OnOverlapBegin(::testing::_)).Times(0);

    // Set expectations for entity 2
    EXPECT_CALL(m_CollisionCallback2, OnOverlapBegin(::testing::_)).Times(0);


    // Execute
    m_ECS.GetComponent<tabi::Transform>(m_Entity1).m_Position = tabi::vec3{ 0.0f, 0.0f, 0.0f };
    m_ECS.GetComponent<tabi::Transform>(m_Entity2).m_Position = tabi::vec3{ 1000.0f, 1000.0f, 1000.0f };

    m_ECS.Update(1.0f);
}
