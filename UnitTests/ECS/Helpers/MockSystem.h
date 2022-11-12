#pragma once

#include "ISystem.h"

#include "gmock/gmock.h"

class MockSystem : public tabi::ISystem
{
public:
    MockSystem(tabi::ComponentManager* a_ComponentManager)
        : ISystem(a_ComponentManager) {}

    MOCK_METHOD(void, OnUpdate, (float a_DeltaTime), (override));
};
