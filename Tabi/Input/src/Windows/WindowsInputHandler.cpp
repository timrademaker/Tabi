#pragma once

#include "Windows/WindowsInputHandler.h"

#include "Enums/EMouse.h"
#include "Enums/EKeyboard.h"
#include "Enums/EInputDevice.h"

#include <Logging.h>

#include <TabiMacros.h>

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
	, m_WindowHandle(tabi::graphics::IWindow::GetInstance().GetHandle())
{
    m_InputDeviceTable[EInputDevice::Controller] = m_GaInputManager.CreateDevice<gainput::InputDevicePad>();
    m_InputDeviceTable[EInputDevice::Keyboard] = m_GaInputManager.CreateDevice<gainput::InputDeviceKeyboard>();
    m_InputDeviceTable[EInputDevice::Mouse] = m_GaInputManager.CreateDevice<gainput::InputDeviceMouse>();

    // Raw input device
    m_RawInputDevice.hwndTarget = nullptr;
    m_RawInputDevice.dwFlags = 0;
    m_RawInputDevice.usUsagePage = 0x01;
    m_RawInputDevice.usUsage = 0x02;
    TABI_ASSERT(RegisterRawInputDevices(&m_RawInputDevice, 1, sizeof(m_RawInputDevice)) == TRUE && "Unable to register raw input device!");
}

void tabi::InputHandler::Update()
{
    GetWindowRect(m_WindowHandle, &m_WindowRect);
    m_WindowWidth = m_WindowRect.right - m_WindowRect.left;
    m_WindowHeight = m_WindowRect.bottom - m_WindowRect.top;
    m_GaInputManager.SetDisplaySize(m_WindowWidth, m_WindowHeight);

    m_MouseDeltaX = 0;
    m_MouseDeltaY = 0;

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
        const EInputDevice deviceType = DetermineDeviceType(a_Button);
        m_InputMap.MapBool(a_Button, ConvertDeviceType(deviceType), ConvertButton(a_Button));
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
        const EInputDevice deviceType = DetermineDeviceType(a_Axis);
        m_InputMap.MapFloat(a_Axis, ConvertDeviceType(deviceType), ConvertButton(a_Axis));
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
        TABI_WARN("Trying to get button state for an unbound button: %d", a_Button);
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
        const float pos = m_InputMap.GetFloat(a_Axis);
        if (a_Delta)
        {
            if (a_Axis == static_cast<unsigned>(EMouse::MouseX))
            {
                *a_Delta = static_cast<float>(m_MouseDeltaX) / static_cast<float>(m_WindowWidth);
            }
            else if (a_Axis == static_cast<unsigned>(EMouse::MouseY))
            {
                *a_Delta = static_cast<float>(m_MouseDeltaY) / static_cast<float>(m_WindowHeight);
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
        TABI_WARN("Trying to get button state for an unbound axis: %d", a_Axis);
        return 0.0f;
    }
}

void tabi::InputHandler::SetMouseCursorVisible(bool a_Visible)
{
    m_HideCursor = !a_Visible;

    SetCursorVisible(a_Visible);
}

void tabi::InputHandler::SetMouseCursorCapture(bool a_Capture)
{
    m_CaptureMouse = a_Capture;
}

void tabi::InputHandler::HandleMsg(const MSG& a_Msg)
{
    m_GaInputManager.HandleMessage(a_Msg);

    // Handle raw mouse input
    if (a_Msg.message == WM_INPUT)
    {
        UINT size;
        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(a_Msg.lParam), RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) == -1)
        {
            return;
        }
        
        m_RawBuffer.resize(size);


        if (GetRawInputData(reinterpret_cast<HRAWINPUT>(a_Msg.lParam), RID_INPUT, m_RawBuffer.data(), &size, sizeof(RAWINPUTHEADER)) != size)
        {
            return;
        }

        auto& ri = reinterpret_cast<const RAWINPUT&>(*m_RawBuffer.data());
        if (ri.header.dwType == RIM_TYPEMOUSE && (ri.data.mouse.lLastX != 0 || ri.data.mouse.lLastY != 0))
        {
            m_MouseDeltaX += ri.data.mouse.lLastX;
            m_MouseDeltaY += ri.data.mouse.lLastY;
        }
    }
}


unsigned int tabi::InputHandler::ConvertButton(unsigned int a_Button)
{
    const EInputDevice deviceType = DetermineDeviceType(a_Button);
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
        TABI_WARN("Unable to convert mouse button %d", static_cast<unsigned>(a_Button));
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
        TABI_WARN("Unable to convert keyboard button %d", static_cast<unsigned>(a_Button));
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
        TABI_WARN("Unable to convert controller button %d", static_cast<unsigned>(a_Button));
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

    TABI_WARN("Unable to determine device type for button %d", a_Button);
    return EInputDevice();
}

bool tabi::InputHandler::IsBound(unsigned int a_Button) const
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
    if (m_WindowHandle)
    {
        if (GetFocus() != m_WindowHandle)
        {
            // Don't capture if the window doesn't have focus
            m_MouseDeltaX = 0;
            m_MouseDeltaY = 0;

            SetCursorVisible(true);
            return;
        }

        SetCursorVisible(!m_HideCursor);
        SetCursorPos(m_WindowRect.right - (m_WindowWidth / 2), m_WindowRect.bottom - (m_WindowHeight / 2));
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
        TABI_WARN("Unable to convert input device %d", static_cast<unsigned>(a_Device));
        return 0;
    }
}
