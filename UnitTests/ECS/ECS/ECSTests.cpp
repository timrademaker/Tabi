#include "ECS.h"

#include "MockSystem.h"
#include "TestComponent.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(ECSTests, SystemUpdate)
{
    // Setup
    tabi::ECS ecs;
    tabi::shared_ptr<MockSystem> registeredSystem = ecs.RegisterSystem<MockSystem>();

    // Set expectations
    EXPECT_CALL(*registeredSystem, OnUpdate(::testing::_)).Times(4);

    // Execute
    for (int i = 0; i < 4; ++i)
    {
        ecs.Update(0.0f);
    }
}

TEST(ECSTests, GetComponent)
{
    static constexpr size_t NumberOfEntities = 10;

    tabi::ECS ecs;
    TestComponent tc;

    tabi::vector<tabi::pair<tabi::Entity, size_t>> entitiesWithExpectedValue;
    for(int32_t i = 0; i < NumberOfEntities; ++i)
    {
        tabi::Entity entity = ecs.CreateEntity();
        entitiesWithExpectedValue.push_back({ entity, i });

        tc.m_Variable = i;
        ecs.AddComponent(entity, tc);
    }

    for (const auto ent : entitiesWithExpectedValue)
    {
        const auto& comp = ecs.GetComponent<TestComponent>(ent.first);
        EXPECT_EQ(comp.m_Variable, ent.second);
    }

    // Delete some components and check if we still get the correct components back
    for (int32_t i = entitiesWithExpectedValue.size() - 1; i >= 0; --i)
    {
        if(i % 2 == 0)
        {
            ecs.DestroyEntity(entitiesWithExpectedValue[i].first);
            entitiesWithExpectedValue.erase(entitiesWithExpectedValue.begin() + i);
        }
    }

    for (const auto ent : entitiesWithExpectedValue)
    {
        const auto& comp = ecs.GetComponent<TestComponent>(ent.first);
        EXPECT_EQ(comp.m_Variable, ent.second);
    }
}
