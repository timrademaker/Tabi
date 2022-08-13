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

    for (auto buttonIter = manager.m_BoundButtons.begin(); buttonIter != manager.m_BoundButtons.end(); ++buttonIter)
    {
        bool isDown = false;
        bool downLastFrame = false;

        switch (DetermineDeviceType(buttonIter->first))
        {
        case EInputDevice::Mouse:
        {
            isDown = handler.IsButtonDown(static_cast<EMouse>(buttonIter->first), &downLastFrame);
            break;
        }
        case EInputDevice::Keyboard:
        {
            isDown = handler.IsButtonDown(static_cast<EKeyboard>(buttonIter->first), &downLastFrame);
            break;
        }
        case EInputDevice::Controller:
        {
            isDown = handler.IsButtonDown(static_cast<EController>(buttonIter->first), &downLastFrame);
            break;
        }

        default:
            TABI_ASSERT(false);
        }

        if (isDown)
        {
            buttonIter->second.m_ButtonDownCallback.Broadcast(tabi::ButtonDownEvent{ !downLastFrame });
        }
        else if(downLastFrame)
        {
            buttonIter->second.m_ButtonUpCallback.Broadcast();
        }
    }

    // TODO: IInputHandler is currently expected to handle buttons from EMouse and EController as well. Not sure if that makes sense.
    // Maybe split up each device into devicetype::EButton and devicetype::EAxis? (But what are L2 and R2?)
    for (auto axisIter = manager.m_BoundAxes.begin(); axisIter != manager.m_BoundAxes.end(); ++axisIter)
    {
        float delta = 0.0f;
        float val = 0.0f;
        switch (DetermineDeviceType(axisIter->first))
        {
        case EInputDevice::Mouse:
        {
            val = handler.GetAxisValue(static_cast<EMouse>(axisIter->first), &delta);
            break;
        }
        case EInputDevice::Keyboard:
        {
            bool downLastFrame = false;
            const bool isDown = handler.IsButtonDown(static_cast<EKeyboard>(axisIter->first), &downLastFrame);
            val = isDown ? 1.0f : 0.0f;

            if(isDown && !downLastFrame)
            {
                delta = 1.0f;
            }
            else if(!isDown && downLastFrame)
            {
                delta = -1.0f;
            }

            break;
        }
        case EInputDevice::Controller:
        {
            val = handler.GetAxisValue(static_cast<EController>(axisIter->first), &delta);
            break;
        }

        default:
            TABI_ASSERT(false);
        }

        axisIter->second.Broadcast(tabi::AxisEvent{ val, delta });
    }

    handler.Update();
}

void tabi::InputManager::SetCursorVisible(bool a_ShowCursor)
{
    IInputHandler::GetInstance().SetMouseCursorVisible(a_ShowCursor);
}

void tabi::InputManager::SetCursorCapture(bool a_Capture)
{
    IInputHandler::GetInstance().SetMouseCursorCapture(a_Capture);
}

void tabi::InputManager::UnbindButtonInternal(unsigned int a_Button, void* a_Object)
{
    // Check if the button is bound
    const auto iter = m_BoundButtons.find(a_Button);
    if (iter != m_BoundButtons.end())
    {
        const auto& buttonEvent = iter->second;
        bool foundAny = buttonEvent.m_ButtonDownCallback.Unsubscribe(a_Object);
        foundAny |= buttonEvent.m_ButtonUpCallback.Unsubscribe(a_Object);

#if defined(_DEBUG)
        if (!foundAny)
        {
            TABI_WARN("Unable to unbind button %d as it wasn't bound", a_Button);
        }
#else
        TABI_UNUSED(foundAny);
#endif
    }
}

void tabi::InputManager::BindAxisInternal(unsigned int a_Axis, void* a_Object, AxisHandlerSignature a_Callback)
{
    m_BoundAxes[a_Axis].Subscribe(a_Object, a_Callback);
}

void tabi::InputManager::UnbindAxisInternal(unsigned int a_Axis, void* a_Object)
{
    // Check if the axis is bound
    const auto iter = m_BoundAxes.find(a_Axis);
    if (iter != m_BoundAxes.end())
    {
        const auto& axisEvent = iter->second;
        bool foundAny = axisEvent.Unsubscribe(a_Object);

#if defined(_DEBUG)
        if (!foundAny)
        {
            TABI_WARN("Unable to unbind axis %d as it wasn't bound", a_Axis);
        }
#else
        TABI_UNUSED(foundAny);
#endif
    }
}

tabi::EInputDevice InputManager::DetermineDeviceType(unsigned a_Button)
{
    if (a_Button & static_cast<unsigned>(EInputDevice::Controller))
    {
        return EInputDevice::Controller;
    }
    else if (a_Button & static_cast<unsigned>(EInputDevice::Keyboard))
    {
        return EInputDevice::Keyboard;
    }
    else if (a_Button & static_cast<unsigned>(EInputDevice::Mouse))
    {
        return EInputDevice::Mouse;
    }

    TABI_ASSERT(false, "Unable to determine device type");
    return {};
}

InputManager& InputManager::GetInstance()
{
    static InputManager instance;

    return instance;
}
