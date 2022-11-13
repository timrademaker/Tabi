#pragma once

#include "ISystem.h"

#include "gmock/gmock.h"

class MockSystem : public tabi::ISystem
{
    struct MockComponent
    {
        size_t a;
    };

public:
    MockSystem(tabi::ComponentManager* a_ComponentManager)
        : ISystem(a_ComponentManager)
    {
        RequireComponent<MockComponent>();
    }

    MOCK_METHOD(void, OnUpdate, (float a_DeltaTime), (override));
};
