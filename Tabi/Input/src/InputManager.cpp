#include "InputManager.h"

#include "IInputHandler.h"

#include <Logging.h>

using tabi::InputManager;


void tabi::InputManager::UnbindButton(EMouse a_Button, void* a_Object)
{
    GetInstance().UnbindButtonInternal(static_cast<unsigned>(a_Button), a_Object);
}

void tabi::InputManager::UnbindButton(EKeyboard a_Button, void* a_Object)
{
    GetInstance().UnbindButtonInternal(static_cast<unsigned>(a_Button), a_Object);
}

void tabi::InputManager::UnbindButton(EController a_Button, void* a_Object)
{
    GetInstance().UnbindButtonInternal(static_cast<unsigned>(a_Button), a_Object);
}

void tabi::InputManager::UnbindAxis(EMouse a_Axis, void* a_Object)
{
    GetInstance().UnbindAxisInternal(static_cast<unsigned>(a_Axis), a_Object);
}

void tabi::InputManager::UnbindAxis(EKeyboard a_Axis, void* a_Object)
{
    GetInstance().UnbindAxisInternal(static_cast<unsigned>(a_Axis), a_Object);
}

void tabi::InputManager::UnbindAxis(EController a_Axis, void* a_Object)
{
    GetInstance().UnbindAxisInternal(static_cast<unsigned>(a_Axis), a_Object);
}

void tabi::InputManager::UnbindAllButtons(void* a_Object)
{
    auto& instance = GetInstance();
    
    for(auto& mapIter : instance.m_BoundButtons)
    {
        instance.UnbindButtonInternal(mapIter.first, a_Object);
    }
}

void tabi::InputManager::UnbindAllAxes(void* a_Object)
{
    auto& instance = GetInstance();

    for (auto& mapIter : instance.m_BoundAxes)
    {
        instance.UnbindAxisInternal(mapIter.first, a_Object);
    }
}

bool tabi::InputManager::AnyButtonDown()
{
    return IInputHandler::GetInstance().AnyButtonDown();
}

void InputManager::Update()
{
    auto& manager = GetInstance();
    auto& handler = IInputHandler::GetInstance();
    handler.Update();

    for (BoundButtonMap::iterator buttonIter = manager.m_BoundButtons.begin(); buttonIter != manager.m_BoundButtons.end(); ++buttonIter)
    {
        bool downLastFrame = false;
        if (handler.IsButtonDown(buttonIter->first, &downLastFrame))
        {
            buttonIter->second.Broadcast(tabi::ButtonEvent{ downLastFrame });
        }
    }

    for (BoundAxesMap::iterator axisIter = manager.m_BoundAxes.begin(); axisIter != manager.m_BoundAxes.end(); ++axisIter)
    {
        float delta = 0.0f;
        float val = handler.GetAxisValue(axisIter->first, &delta);
        axisIter->second.Broadcast(tabi::AxisEvent{ val, delta });
    }
}

void tabi::InputManager::SetCursorMode(bool a_HideCursor, bool a_CaptureCursor)
{
    IInputHandler::GetInstance().SetMouseCursorMode(a_HideCursor, a_CaptureCursor);
}

void tabi::InputManager::BindButtonInternal(unsigned int a_Button, void* a_Object, ButtonHandlerSignature a_Callback)
{
    IInputHandler::GetInstance().BindButton(a_Button);
    m_BoundButtons[a_Button].Subscribe(a_Object, a_Callback);
};

void tabi::InputManager::UnbindButtonInternal(unsigned int a_Button, void* a_Object)
{
    // Check if the button is bound
    auto iter = m_BoundButtons.find(a_Button);
    if (iter != m_BoundButtons.end())
    {
        auto& buttonEvent = iter->second;
        bool foundAny = buttonEvent.Unsubscribe(a_Object);

#if defined(_DEBUG)
        if (!foundAny)
        {
            tabi::logger::TabiWarn("Unable to unbind button " + tabi::to_string(a_Button) + " as it wasn't bound");
        }
#else
        TABI_UNUSED(foundAny);
#endif
        
        // If there's no more subscribers, unbind in IInputHandler
        if (!buttonEvent.HasSubscribers())
        {
            IInputHandler::GetInstance().UnbindButton(a_Button);
        }
    }
}

void tabi::InputManager::BindAxisInternal(unsigned int a_Axis, void* a_Object, AxisHandlerSignature a_Callback)
{
    IInputHandler::GetInstance().BindAxis(a_Axis);
    m_BoundAxes[a_Axis].Subscribe(a_Object, a_Callback);
}

void tabi::InputManager::UnbindAxisInternal(unsigned int a_Axis, void* a_Object)
{
    // Check if the axis is bound
    auto iter = m_BoundAxes.find(a_Axis);
    if (iter != m_BoundAxes.end())
    {
        auto& axisEvent = iter->second;
        bool foundAny = axisEvent.Unsubscribe(a_Object);

#if defined(_DEBUG)
        if (!foundAny)
        {
            tabi::logger::TabiWarn("Unable to unbind axis " + tabi::to_string(a_Axis) + " as it wasn't bound");
        }
#else
        TABI_UNUSED(foundAny);
#endif

        // If there's no more subscribers, unbind in IInputHandler
        if (!axisEvent.HasSubscribers())
        {
            IInputHandler::GetInstance().UnbindAxis(a_Axis);
        }
    }
}


InputManager& InputManager::GetInstance()
{
    static InputManager instance;

    return instance;
}