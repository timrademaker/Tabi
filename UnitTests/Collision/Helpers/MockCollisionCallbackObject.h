#pragma once

#include "gmock/gmock.h"

#include <ECS/ColliderComponent.h>

class MockCollisionCallbackObject
{
public:
    MOCK_METHOD(void, OnOverlapBegin, (tabi::OverlapInfo a_Info), ());
    MOCK_METHOD(void, OnOverlapEnd, (tabi::OverlapInfo a_Info), ());
};
