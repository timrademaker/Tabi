#include "ECS.h"
#include "SystemManager.h"

#include "MockSystem.h"

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
