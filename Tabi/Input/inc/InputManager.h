#pragma once

#include <TabiContainers.h>
#include <TabiEvent.h>

#include <functional>

namespace tabi
{
    enum class EInputDevice;
    enum class EMouse;
    enum class EKeyboard;
    enum class EController;

    struct ButtonDownEvent
    {
        /// True if the button went down between last frame and this frame
        bool m_FirstDown;
    };

    struct AxisEvent
    {
        /// The current position on the axis, in range [-1.0, 1.0]
        float m_AxisValue;
        /// The difference in position on the axis between the previous frame and this frame
        float m_Delta;
    };

    class InputManager
    {
        DECLARE_EVENT(ButtonDownCallbackEvent, ButtonDownEvent);
        DECLARE_EVENT(AxisCallbackEvent, AxisEvent);

        using ButtonDownHandlerSignature = ButtonDownCallbackEvent::CallbackType;
        using ButtonUpHandlerSignature = Event::CallbackType;

        struct ButtonCallbacks
        {
            ButtonDownCallbackEvent m_ButtonDownCallback;
            Event m_ButtonUpCallback;
        };

        using ButtonDownEventMap = tabi::unordered_map<unsigned int, ButtonCallbacks>;
        
        using AxisHandlerSignature = std::function<void(AxisEvent)>;
        using AxisEventMap = tabi::unordered_map<unsigned int, AxisCallbackEvent>;

    public:
        /**
        * @brief Bind an object to receive events if a specific button is pressed
        * @param a_Button The button the object should receive events for
        * @param a_Object The object that should receive events
        * @param a_ButtonDownCallback The function that should be called when the specified button is pressed
        * @param a_ButtonUpCallback The function that should be called when the specified button is released
        */
        template<typename UserClass>
        static void BindButton(EMouse a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)() = nullptr);
        template<typename UserClass>
        static void BindButton(EKeyboard a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)() = nullptr);
        template<typename UserClass>
        static void BindButton(EController a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)() = nullptr);

        /**
        * @brief Bind an object to receive events if a specific axis is moved
        * @param a_Axis The axis the object should receive events for
        * @param a_Object The object that should receive events
        * @param a_Callback The function that should be called when the specified axis is moved
        */
        template<typename UserClass>
        static void BindAxis(EMouse a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));
        template<typename UserClass>
        static void BindAxis(EKeyboard a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));
        template<typename UserClass>
        static void BindAxis(EController a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent));

        /**
        * @brief Unbind a specific button for an object
        * @param a_Button The button to stop receiving events for
        * @param a_Object The object that should no longer receive input from the specified button
        */
        static void UnbindButton(EMouse a_Button, void* a_Object);
        static void UnbindButton(EKeyboard a_Button, void* a_Object);
        static void UnbindButton(EController a_Button, void* a_Object);
        /**
        * @brief Unbind a specific axis for an object
        * @param a_Axis The axis to stop receiving events for
        * @param a_Object The object that should no longer receive input from the specified axis
        */
        static void UnbindAxis(EMouse a_Axis, void* a_Object);
        static void UnbindAxis(EKeyboard a_Axis, void* a_Object);
        static void UnbindAxis(EController a_Axis, void* a_Object);

        /**
        * @brief Unbind all buttons for an object
        * @param a_Object The object that should no longer receive button input
        */
        static void UnbindAllButtons(void* a_Object);
        /**
        * @brief Unbind all axes for an object
        * @param a_Object The object that should no longer receive axis input
        */
        static void UnbindAllAxes(void* a_Object);

        /**
        * @brief Checks if any button is down
        * @returns True if any button is down
        */
        static bool AnyButtonDown();

        /**
        * @brief Updates user input and calls callback functions if a button was pressed
        */
        static void Update();

        /**
        * @brief Sets the cursor's visibility
        * @param a_ShowCursor Whether the cursor should be visible while it is in the window or not
        */
        static void SetCursorVisible(bool a_ShowCursor);

        /**
        * @brief Confine the cursor to the window
        * @param a_Capture Whether the cursor should be captured or not
        */
        static void SetCursorCapture(bool a_Capture);

    private:
        InputManager() = default;
        ~InputManager() = default;

        template<typename ButtonEnumType, typename UserClass>
        void BindButtonInternal(ButtonEnumType a_Button, UserClass * a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass:: * a_ButtonUpCallback)());

        void UnbindButtonInternal(unsigned int a_Button, void* a_Object);
        void BindAxisInternal(unsigned int a_Axis, void* a_Object, AxisHandlerSignature a_Callback);
        void UnbindAxisInternal(unsigned int a_Axis, void* a_Object);

        static EInputDevice DetermineDeviceType(unsigned int a_Button);

        static InputManager& GetInstance(); // Used for the internal instance

    private:
        ButtonDownEventMap m_BoundButtons;
        AxisEventMap m_BoundAxes;
    };

    template<typename UserClass>
    inline void InputManager::BindButton(EMouse a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        GetInstance().BindButtonInternal(a_Button, a_Object, a_ButtonDownCallback, a_ButtonUpCallback);
    }

    template<typename UserClass>
    inline void InputManager::BindButton(EKeyboard a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        GetInstance().BindButtonInternal(a_Button, a_Object, a_ButtonDownCallback, a_ButtonUpCallback);
    }

    template<typename UserClass>
    inline void InputManager::BindButton(EController a_Button, UserClass* a_Object, void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        GetInstance().BindButtonInternal(a_Button, a_Object, a_ButtonDownCallback, a_ButtonUpCallback);
    }

    template<typename UserClass>
    inline void InputManager::BindAxis(EMouse a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, boundFunction);
    }

    template<typename UserClass>
    inline void InputManager::BindAxis(EKeyboard a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, boundFunction);
    }

    template<typename UserClass>
    inline void InputManager::BindAxis(EController a_Axis, UserClass* a_Object, void(UserClass::* a_Callback)(AxisEvent))
    {
        auto boundFunction = std::bind(a_Callback, a_Object, std::placeholders::_1);
        GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, boundFunction);
    }

    template <typename ButtonEnumType, typename UserClass>
    void InputManager::BindButtonInternal(ButtonEnumType a_Button, UserClass* a_Object,
        void(UserClass::* a_ButtonDownCallback)(ButtonDownEvent), void(UserClass::* a_ButtonUpCallback)())
    {
        if (a_ButtonDownCallback)
        {
            const ButtonDownHandlerSignature buttonDownFunc = std::bind(a_ButtonDownCallback, a_Object, std::placeholders::_1);
            m_BoundButtons[static_cast<unsigned>(a_Button)].m_ButtonDownCallback.Subscribe(a_Object, buttonDownFunc);
        }

        if (a_ButtonUpCallback)
        {
            const ButtonUpHandlerSignature buttonUpFunc = std::bind(a_ButtonUpCallback, a_Object);
            m_BoundButtons[static_cast<unsigned>(a_Button)].m_ButtonUpCallback.Subscribe(a_Object, buttonUpFunc);
        }
    }
}
