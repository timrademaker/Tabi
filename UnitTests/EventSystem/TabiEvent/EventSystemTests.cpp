#include "TestEvent.h"
#include "MockObject.h"

#include "TabiEvent.h"

#include "gtest/gtest.h"

TEST(EventSystemTests, ObjectEventSubscription)
{
    // Create event
    DECLARE_EVENT(TestEv, TestEvent);
    TestEv ev;
    // Create object and subscribe to event
    MockObject mo;
    ev.Subscribe(&mo, &MockObject::EventCallback);
    ASSERT_TRUE(ev.HasSubscribers());

    ev.Unsubscribe(&mo);
    EXPECT_FALSE(ev.HasSubscribers());
}

TEST(EventSystemTests, StaticFunctionEventSubscription)
{
    // Create event
    DECLARE_EVENT(TestEv, TestEvent);
    TestEv ev;
    
    // Subscrive static function to event
    ev.SubscribeStatic(StaticEventCallback);
    ASSERT_TRUE(ev.HasSubscribers());

    ev.UnsubscribeStatic();
    EXPECT_FALSE(ev.HasSubscribers());
}

TEST(EventSystemTests, EventBroadcast)
{
    // Create event
    DECLARE_EVENT(TestEv, int);
    TestEv ev;
    // Create object and subscribe to event
    MockObject mo;
    ev.Subscribe(&mo, &MockObject::IntEventCallback);
    ASSERT_TRUE(ev.HasSubscribers());

    const int expectedEvent = 60;
    EXPECT_CALL(mo, IntEventCallback(expectedEvent)).Times(1);

    // Broadcast event
    ev.Broadcast(expectedEvent);
}

TEST(EventSystemTests, UnsubscribeAll)
{
    // Create event
    DECLARE_EVENT(TestEv, TestEvent);
    TestEv ev;

    // Subscrive (static) function to event
    ev.SubscribeStatic(StaticEventCallback);
    MockObject mo;
    ev.Subscribe(&mo, &MockObject::EventCallback);
    ASSERT_TRUE(ev.HasSubscribers());

    ev.UnsubscribeAll();
    EXPECT_FALSE(ev.HasSubscribers());

    EXPECT_CALL(mo, EventCallback(::testing::_)).Times(0);
    ev.Broadcast({});
}

TEST(EventSystemTests, SubscribeToEmptyEvent)
{
    // Create event
    tabi::Event ev;
    // Create object and subscribe to event
    MockObject mo;
    ev.Subscribe(&mo, &MockObject::EmptyEventCallback);
    ASSERT_TRUE(ev.HasSubscribers());

    EXPECT_CALL(mo, EmptyEventCallback()).Times(1);

    // Broadcast event
    ev.Broadcast();
}
