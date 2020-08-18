#pragma once

#include <TabiTypes.h>

#include <assert.h>
#include <functional>

#define DECLARE_EVENT(EventName, EventClass) \
    using EventName = tabi::EventBase<EventClass>


namespace tabi
{
    template<typename EventInfo>
    class EventBase
    {
        using CallbackType = std::function<void(EventInfo)>;
        using CallbackMap = tabi::unordered_map<void*, tabi::vector<CallbackType>>;
    public:
        EventBase() = default;
        ~EventBase() = default;

        /**
        * @brief Subscribe a callback to an event
        * @params a_Object The object subscribing to the event
        * @params a_Callback The callback function to send events to
        */
        template<typename UserClass>
        void Add(UserClass* a_Object, void(UserClass::* a_Callback)(EventInfo));
        /**
        * @brief Subscribe an object's callback to an event
        * @params a_Object The object subscribing to the event
        * @params a_Callback The callback function to send events to
        */
        template<typename UserClass>
        void Add(UserClass* a_Object, void(UserClass::* a_Callback)());
        /**
        * @brief Subscribe a static function to an event
        * @params a_Callback The callback function to send events to
        */
        void AddStatic(CallbackType a_Callback);
        /**
        * @brief Unsubscribes an object from events
        * @params a_Object The object to unsubscribe
        */
        void Remove(void* a_Object);
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
        /**
        * @brief Internal function that stores callbacks
        * @params a_Object The object subscribing to the event
        * @params a_Callback The callback function to send events to
        */
        void Add_Internal(void* a_Object, CallbackType a_Callback);

    private:
        CallbackMap m_Callbacks;

    };

    template<typename EventInfo>
    template<typename UserClass>
    inline void tabi::EventBase<EventInfo>::Add(UserClass* a_Object, void(UserClass::* a_Callback)(EventInfo))
    {
        assert(a_Object);
        assert(a_Callback);

        auto bound = std::bind(a_Callback, a_Object, std::placeholders::_1);
        Add_Internal(a_Object, bound);
    }

    template<typename EventInfo>
    template<typename UserClass>
    inline void tabi::EventBase<EventInfo>::Add(UserClass* a_Object, void(UserClass::* a_Callback)())
    {
        assert(a_Object);
        assert(a_Callback);

        auto bound = std::bind(a_Callback, a_Object);
        Add_Internal(a_Object, bound);
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::AddStatic(CallbackType a_Callback)
    {
        return Add_Internal(nullptr, a_Callback);
    }


    template<typename EventInfo>
    inline void EventBase<EventInfo>::Remove(void* a_Object)
    {
        auto iter = m_Callbacks.find(a_Object);
        if (iter != m_Callbacks.end())
        {
            m_Callbacks.erase(iter);
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
        m_Callbacks.clear();
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::Broadcast(EventInfo a_Event)
    {
        for (auto iter = m_Callbacks.begin(); iter != m_Callbacks.end(); ++iter)
        {
            for (CallbackType& d : iter->second)
            {
                d(a_Event);
            }
        }
    }

    template<typename EventInfo>
    inline void EventBase<EventInfo>::Add_Internal(void* a_Object, CallbackType a_Callback)
    {
        if (a_Callback)
        {
            m_Callbacks[a_Object].push_back(a_Callback);
        }
#if defined(_DEBUG)
        else
        {
            tabi::logger::TabiWarn("[TabiEvent] Trying to add a callback that isn't valid!");
        }
#endif
    }

    struct EmptyEvent {};
    using Delegate = tabi::EventBase<EmptyEvent>;
}
