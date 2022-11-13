#include "SystemManager.h"

#include "MockSystem.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(SystemManagerTests, SystemRegistration)
{
    tabi::ComponentManager compMan;
    tabi::SystemManager sysMan;

    const tabi::shared_ptr<MockSystem> registeredSystem = sysMan.RegisterSystem<MockSystem>(&compMan);

    EXPECT_EQ(sysMan.GetSystem<MockSystem>().get(), registeredSystem.get());
}
