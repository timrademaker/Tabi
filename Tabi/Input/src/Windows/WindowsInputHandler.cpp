#pragma once

#include "Windows/WindowsInputHandler.h"

#include "Enums/EMouse.h"
#include "Enums/EKeyboard.h"
#include "Enums/EInputDevice.h"

#include <Logging.h>

#include <TabiMacros.h>

#include <IRenderer.h>
#include <IWindow.h>

DISABLE_WARNING_PUSH
DISABLE_ALL_WARNINGS
#include <gainput/gainput.h>
#include <gainput/GainputInputManager.h>
#include <gainput/GainputInputMap.h>
DISABLE_WARNING_POP

using tabi::EMouse;
using tabi::EKeyboard;
using tabi::EController;
using tabi::EInputDevice;

tabi::InputHandler::InputHandler()
    : m_InputMap(m_GaInputManager)
    , m_MouseDeltaX(0.0f)
    , m_MouseDeltaY(0.0f)
{
    tabi::graphics::IRenderer::GetInstance().GetWindowDimensions(m_WindowWidth, m_WindowHeight);

    m_GaInputManager.SetDisplaySize(m_WindowWidth, m_WindowHeight);

    //m_InputDeviceTable[EInputDevice::Controller] = m_GaInputManager.CreateDevice<gainput::InputDevicePad>();
    m_InputDeviceTable[EInputDevice::Keyboard] = m_GaInputManager.CreateDevice<gainput::InputDeviceKeyboard>();
    m_InputDeviceTable[EInputDevice::Mouse] = m_GaInputManager.CreateDevice<gainput::InputDeviceMouse>();
}

void tabi::InputHandler::Update()
{
    m_GaInputManager.Update();

    if (m_CaptureMouse)
    {
        CaptureCursor();
    }
}

void tabi::InputHandler::BindButton(unsigned int a_Button)
{
    if (!IsBound(a_Button))
    {
        EInputDevice deviceType = DetermineDeviceType(a_Button);
        auto device = ConvertDeviceType(deviceType);
        unsigned int convertedButton = ConvertButton(a_Button);

        m_InputMap.MapBool(a_Button, device, convertedButton);
    }
}

void tabi::InputHandler::UnbindButton(unsigned int a_Button)
{
    if (IsBound(a_Button))
    {
        m_InputMap.Unmap(a_Button);
    }

}

void tabi::InputHandler::BindAxis(unsigned int a_Axis)
{
    if (!IsBound(a_Axis))
    {
        EInputDevice deviceType = DetermineDeviceType(a_Axis);
        auto device = ConvertDeviceType(deviceType);
        unsigned int convertedButton = ConvertButton(a_Axis);

        m_InputMap.MapFloat(a_Axis, device, convertedButton);
    }
}

void tabi::InputHandler::UnbindAxis(unsigned int a_Axis)
{
    if (IsBound(a_Axis))
    {
        m_InputMap.Unmap(a_Axis);
    }
}

bool tabi::InputHandler::IsButtonDown(unsigned int a_Button, bool* a_DownLastFrame)
{
    if (IsBound(a_Button))
    {
        if (a_DownLastFrame)
        {
            *a_DownLastFrame = m_InputMap.GetBoolIsNew(a_Button);
        }

        return m_InputMap.GetBool(a_Button);
    }
    else
    {
        logger::TabiWarn("Trying to get button state for an unbound button: " + tabi::to_string(a_Button));
        return false;
    }
}

bool tabi::InputHandler::AnyButtonDown()
{
    gainput::DeviceButtonSpec spec;
    return m_GaInputManager.GetAnyButtonDown(&spec, 1) > 0;
}

float tabi::InputHandler::GetAxisValue(unsigned int a_Axis, float* a_Delta)
{
    if (IsBound(a_Axis))
    {
        float pos = m_InputMap.GetFloat(a_Axis);
        if (a_Delta)
        {
            if (a_Axis == static_cast<unsigned>(EMouse::MouseX) && m_CaptureMouse)
            {
                *a_Delta = m_MouseDeltaX;
            }
            else if (a_Axis == static_cast<unsigned>(EMouse::MouseY) && m_CaptureMouse)
            {
                *a_Delta = m_MouseDeltaY;
            }
            else
            {
                *a_Delta = m_InputMap.GetFloatDelta(a_Axis);
            }
        }

        return pos;
    }
    else
    {
        logger::TabiWarn("Trying to get button state for an unbound axis: " + tabi::to_string(a_Axis));
        return 0.0f;
    }
}

void tabi::InputHandler::SetMouseCursorMode(bool a_Visible, bool a_Capture)
{
    m_HideCursor = a_Visible;
    m_CaptureMouse = a_Capture;

    SetCursorVisible(a_Visible);
}

void tabi::InputHandler::HandleMsg(const MSG& a_Msg)
{
    m_GaInputManager.HandleMessage(a_Msg);
}


unsigned int tabi::InputHandler::ConvertButton(unsigned int a_Button)
{
    EInputDevice deviceType = DetermineDeviceType(a_Button);
    unsigned int convertedButton;
    switch (deviceType)
    {
    case tabi::EInputDevice::Mouse:
    {
        convertedButton = ConvertButton(static_cast<EMouse>(a_Button));
        break;
    }
    case tabi::EInputDevice::Keyboard:
    {
        convertedButton = ConvertButton(static_cast<EKeyboard>(a_Button));
        break;
    }
    case tabi::EInputDevice::Controller:
    {
        convertedButton = ConvertButton(static_cast<EController>(a_Button));
        break;
    }
    default:
    {
        convertedButton = 0;
        break;
    }
    }

    return convertedButton;
}

unsigned int tabi::InputHandler::ConvertButton(EMouse a_Button)
{
    const auto& iter = ms_MouseTable.find(a_Button);
    if (iter != ms_MouseTable.end())
    {
        return iter->second;
    }
    else
    {
        logger::TabiWarn("Unable to convert mouse button " + tabi::to_string(static_cast<unsigned>(a_Button)));
        return 0;
    }
}

unsigned int tabi::InputHandler::ConvertButton(EKeyboard a_Button)
{
    const auto& iter = ms_KeyboardTable.find(a_Button);
    if (iter != ms_KeyboardTable.end())
    {
        return iter->second;
    }
    else
    {
        logger::TabiWarn("Unable to convert keyboard button " + tabi::to_string(static_cast<unsigned>(a_Button)));
        return 0;
    }
}

unsigned int tabi::InputHandler::ConvertButton(EController a_Button)
{
    const auto& iter = ms_ControllerTable.find(a_Button);
    if (iter != ms_ControllerTable.end())
    {
        return iter->second;
    }
    else
    {
        logger::TabiWarn("Unable to convert controller button " + tabi::to_string(static_cast<unsigned>(a_Button)));
        return 0;
    }
}

EInputDevice tabi::InputHandler::DetermineDeviceType(unsigned int a_Button)
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

    logger::TabiWarn("Unable to determine device type for button " + tabi::to_string(a_Button));
    return EInputDevice();
}

bool tabi::InputHandler::IsBound(unsigned int a_Button)
{
    return m_InputMap.IsMapped(a_Button);
}

void tabi::InputHandler::SetCursorVisible(bool a_Visible)
{
    if (m_CursorVisible == a_Visible)
    {
        return;
    }

    if (a_Visible)
    {
        while (ShowCursor(true) < 0);
        m_CursorVisible = true;
    }
    else
    {
        while (ShowCursor(false) >= 0);
        m_CursorVisible = false;
    }
}

void tabi::InputHandler::CaptureCursor()
{
    auto& renderer = graphics::IRenderer::GetInstance();

    //HWND window = FindWindow(graphics::Window::GetWindowClassName(), renderer.GetWindow().GetWindowName());
    HWND window = renderer.GetWindow().GetHandle();
    if (window)
    {
        if (GetFocus() != window)
        {
            // Don't capture if the window doesn't have focus
            m_MouseDeltaX = 0.0f;
            m_MouseDeltaY = 0.0f;

            SetCursorVisible(true);
            return;
        }
        SetCursorVisible(false);

        POINT beforePos = { 0 };
        GetCursorPos(&beforePos);

        RECT rect = { 0 };
        GetWindowRect(window, &rect);
        SetCursorPos(rect.right - (m_WindowWidth / 2), rect.bottom - (m_WindowHeight / 2));

        m_WindowWidth = rect.right - rect.left;
        m_WindowHeight = rect.bottom - rect.top;

        POINT afterPos = { 0 };
        GetCursorPos(&afterPos);

        m_MouseDeltaX = (float(beforePos.x - afterPos.x) / float(m_WindowWidth));
        m_MouseDeltaY = (float(beforePos.y - afterPos.y) / float(m_WindowHeight));
    }
}

unsigned int tabi::InputHandler::ConvertDeviceType(EInputDevice a_Device)
{

    const auto& iter = m_InputDeviceTable.find(a_Device);
    if (iter != m_InputDeviceTable.end())
    {
        return iter->second;
    }
    else
    {
        logger::TabiWarn("Unable to convert input device " + tabi::to_string(static_cast<unsigned>(a_Device)));
        return 0;
    }
}