#include "InputManager.h"

#include "IInputHandler.h"

using tabi::InputManager;


void tabi::InputManager::BindButton(EMouse a_Button, UserClass* a_Object, ButtonHandlerSignature a_Callback)
{
    GetInstance().BindButtonInternal(static_cast<unsigned>(a_Button), a_Object, a_Callback);
}

void tabi::InputManager::BindButton(EKeyboard a_Button, UserClass* a_Object, ButtonHandlerSignature a_Callback)
{
    GetInstance().BindButtonInternal(static_cast<unsigned>(a_Button), a_Object, a_Callback);
}

void tabi::InputManager::BindButton(EController a_Button, UserClass* a_Object, ButtonHandlerSignature a_Callback)
{
    GetInstance().BindButtonInternal(static_cast<unsigned>(a_Button), a_Object, a_Callback);
}

void tabi::InputManager::BindAxis(EMouse a_Axis, UserClass* a_Object, AxisHandlerSignature a_Callback)
{
    GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, a_Callback);
}

void tabi::InputManager::BindAxis(EKeyboard a_Axis, UserClass* a_Object, AxisHandlerSignature a_Callback)
{
    GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, a_Callback);
}

void tabi::InputManager::BindAxis(EController a_Axis, UserClass* a_Object, AxisHandlerSignature a_Callback)
{
    GetInstance().BindAxisInternal(static_cast<unsigned>(a_Axis), a_Object, a_Callback);
}

void InputManager::Update()
{
    auto& manager = GetInstance();
    auto& handler = IInputHandler::GetInstance();

    for (BoundButtonMap::iterator buttonIter = manager.m_BoundButtons.begin(); buttonIter != manager.m_BoundButtons.end(); ++buttonIter)
    {
        if (handler.IsButtonDown(buttonIter->first))
        {
            for (auto& callbackPair : buttonIter->second)
            {
                // TODO: Check if button went down last frame (store keystate?)
                callbackPair.second(true);
            }
        }
    }

    for (BoundAxesMap::iterator axisIter = manager.m_BoundAxes.begin(); axisIter != manager.m_BoundAxes.end(); ++axisIter)
    {
        float val = handler.GetAxisValue(axisIter->first);
        for (auto& callbackPair : axisIter->second)
        {
            // TODO: Calculate delta
            float delta = 0.0f;
            callbackPair.second(val, delta);
        }
    }
}

void tabi::InputManager::BindButtonInternal(unsigned int a_Button, UserClass* a_Object, ButtonHandlerSignature a_Callback)
{
    // TODO: If debugging, check if the callback is already registered for the object
    m_BoundButtons[a_Button].push_back(tabi::make_pair(a_Object, a_Callback));
};

void tabi::InputManager::BindAxisInternal(unsigned int a_Axis, UserClass* a_Object, AxisHandlerSignature a_Callback)
{
    // TODO: If debugging, check if the callback is already registered for the object
    m_BoundAxes[a_Axis].push_back(tabi::make_pair(a_Object, a_Callback));
}


InputManager& InputManager::GetInstance()
{
    static InputManager instance;

    return instance;
}