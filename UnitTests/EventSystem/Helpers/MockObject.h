#pragma once

#include "TestEvent.h"

#include "gmock/gmock.h"

class MockObject
{
public:
    MOCK_METHOD(void, EventCallback, (TestEvent a_Event));
    MOCK_METHOD(void, IntEventCallback, (int a_Event));
};

void StaticEventCallback(TestEvent) {}
