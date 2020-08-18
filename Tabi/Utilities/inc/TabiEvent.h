#pragma once

#include <TabiTypes.h>

#include <functional>

#define DECLARE_EVENT(EventName, EventClass) \
    using EventName = tabi::EventBase<EventClass>

/**
* @brief Helper macros to subscribe to events
* @params Subscriber The object subscribing to the event
* @params Callback The callback function to send events to
*/
#define Subscribe_NoParams(Subscriber, Callback)    Add(&Subscriber, std::bind(&Callback, Subscriber))
#define Subscribe(Subscriber, Callback)             Add(&Subscriber, std::bind(&Callback, Subscriber, std::placeholders::_1))

namespace tabi
{
    template<typename EventInfo>
    class EventBase
    {
        using UserClass = void;

        using DelegateType = std::function<void(EventInfo)>;
        using DelegateMap = tabi::unordered_map<UserClass*, tabi::vector<DelegateType>>;
    public:
        EventBase() = default;
        ~EventBase() = default;

        /**
        * Subscribe an object to an event. You can use the Add-function together with the TABI_BIND-macro (Add(&object, TABI_BIND_OneParam(object, Class::Function))), or the Subscribe-macro (Subscribe(object, Class::Function))
        * @brief Subscribe an object to an event.
        * @params a_Object The object subscribing to the event
        * @params a_Callback The callback function to send events to
        */
        void Add(UserClass* a_Object, DelegateType a_Callback);
        /**
        * @brief Subscribe a static function to an event
        * @params a_Callback The callback function to send events to
        */
        void AddStatic(DelegateType a_Callback);
        /**
        * @brief Unsubscribes an object from events
        * @params a_Object The object to unsubscribe
        */
        void Remove(UserClass* a_Object);
        /**
        * @brief Removes all static subscribers
        */
        void RemoveStatic();
        /**
        * @brief Removes all subscribers
        */
        void RemoveAll();

        /**
        * Broadcasts an event to all subscribers. If ReturnType is bool, a return value of "true", it means the event has been consumed and should not be sent out to other delegates.
        * @brief Broadcasts an event to all subscribers
        * @params a_Event The message sent to all subscribers' callback functions
        */
        void Broadcast(EventInfo a_Event = {});

    private:
        DelegateMap m_Delegates;

    };


    template<typename EventInfo>
    inline void EventBase<EventInfo>::Add(UserClass* a_Object, DelegateType a_Callback)
    {
        if (a_Callback)
        {
            m_Delegates[a_Object].push_back(a_Callback);
        }
#if defined(_DEBUG)
        else
        {
            tabi::logger::TabiWarn("[Delegate] Trying to add a callback that isn't valid!");
        }
#endif

    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::AddStatic(DelegateType a_Callback)
    {
        return Add(nullptr, a_Callback);
    }


    template<typename EventInfo>
    inline void EventBase<EventInfo>::Remove(UserClass* a_Object)
    {
        auto iter = m_Delegates.find(a_Object);
        if (iter != m_Delegates.end())
        {
            m_Delegates.erase(iter);
        }
#if defined(_DEBUG)
        else
        {
            tabi::logger::TabiWarn("Tried to unbind all delegates from an object, but nothing was bound!");
        }
#endif
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::RemoveStatic()
    {
        return Remove(nullptr);
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::RemoveAll()
    {
        m_Delegates.clear();
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::Broadcast(EventInfo a_Event)
    {
        for (auto iter = m_Delegates.begin(); iter != m_Delegates.end(); ++iter)
        {
            for (DelegateType& d : iter->second)
            {
                d(a_Event);
            }
        }
    }

    struct EmptyEvent {};
    using Delegate = tabi::EventBase<EmptyEvent>;
}
