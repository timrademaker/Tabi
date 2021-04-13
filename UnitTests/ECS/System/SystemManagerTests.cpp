#include "SystemManager.h"

#include "MockSystem.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(SystemManagerTests, SystemRegistration)
{
    tabi::SystemManager sysMan;
    tabi::shared_ptr<MockSystem> registeredSystem = sysMan.RegisterSystem<MockSystem>(nullptr);

    EXPECT_EQ(sysMan.GetSystem<MockSystem>(), registeredSystem);
}

TEST(SystemManagerTests, SystemSignature)
{
    tabi::SystemManager sysMan;
    tabi::shared_ptr<MockSystem> registeredSystem = sysMan.RegisterSystem<MockSystem>(nullptr);
    const tabi::SystemSignature expectedSignature{ 0b101 };
    sysMan.SetSystemSignature<MockSystem>(expectedSignature);

    EXPECT_EQ(sysMan.GetSystemSignature<MockSystem>(), expectedSignature);
}
