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

// Value to use as offset for axis binds. The alternative to this would be modifying Gainput's InputMap::MapBool(), as MappedInput mi's input filter function is not set up (which causes a nullptr guard somewhere else to pass)
// TODO: Get rid of this at some point (see TODO in InputManager::Update() - buttons and axes should be split up at some point)
static constexpr unsigned int UserButtonAxisOffset = 100u;

tabi::InputHandler::InputHandler()
    : m_InputMap(m_GaInputManager)
    , m_WindowHandle(tabi::graphics::IWindow::GetInstance().GetHandle())
{
    m_InputDeviceTable[EInputDevice::Controller] = m_GaInputManager.CreateDevice<gainput::InputDevicePad>();
    m_InputDeviceTable[EInputDevice::Keyboard] = m_GaInputManager.CreateDevice<gainput::InputDeviceKeyboard>();
    m_InputDeviceTable[EInputDevice::Mouse] = m_GaInputManager.CreateDevice<gainput::InputDeviceMouse>();

    // Bind all buttons so we can check their state when needed
    for(const auto& btn : ms_MouseTable)
    {
        m_InputMap.MapBool(static_cast<unsigned>(btn.first), ConvertDeviceType(EInputDevice::Mouse), btn.second);
        m_InputMap.MapFloat(static_cast<unsigned>(btn.first) + UserButtonAxisOffset, ConvertDeviceType(EInputDevice::Mouse), btn.second);
    }

    for (const auto& btn : ms_ControllerTable)
    {
        m_InputMap.MapBool(static_cast<unsigned>(btn.first), ConvertDeviceType(EInputDevice::Controller), btn.second);
        m_InputMap.MapFloat(static_cast<unsigned>(btn.first) + UserButtonAxisOffset, ConvertDeviceType(EInputDevice::Controller), btn.second);

    }

    for (const auto& btn : ms_KeyboardTable)
    {
        m_InputMap.MapBool(static_cast<unsigned>(btn.first), ConvertDeviceType(EInputDevice::Keyboard), btn.second);
    }

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
    m_MouseWheelDeltaY = 0;

    m_GaInputManager.Update();

    if (m_CaptureMouse)
    {
        CaptureCursor();
    }
}

bool tabi::InputHandler::IsButtonDown(EKeyboard a_Button, bool* a_DownLastFrame) const
{
    return IsButtonDownInternal(static_cast<unsigned>(a_Button), a_DownLastFrame);
}

bool tabi::InputHandler::IsButtonDown(EController a_Button, bool* a_DownLastFrame) const
{
    return IsButtonDownInternal(static_cast<unsigned>(a_Button), a_DownLastFrame);
}

bool tabi::InputHandler::IsButtonDown(EMouse a_Button, bool* a_DownLastFrame) const
{
    return IsButtonDownInternal(static_cast<unsigned>(a_Button), a_DownLastFrame);
}

bool tabi::InputHandler::AnyButtonDown() const
{
    gainput::DeviceButtonSpec spec;
    return m_GaInputManager.GetAnyButtonDown(&spec, 1) > 0;
}

float tabi::InputHandler::GetAxisValue(EController a_Axis, float* a_Delta) const
{
    return GetAxisValueInternal(static_cast<unsigned>(a_Axis), a_Delta);
}

float tabi::InputHandler::GetAxisValue(EMouse a_Axis, float* a_Delta) const
{
    return GetAxisValueInternal(static_cast<unsigned>(a_Axis), a_Delta);
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
    else if(a_Msg.message == WM_MOUSEWHEEL)
    {
        m_MouseWheelDeltaY += static_cast<float>(GET_WHEEL_DELTA_WPARAM(a_Msg.wParam)) / static_cast<float>(WHEEL_DELTA);
    }
    else if(a_Msg.message == WM_MOUSEMOVE)
    {
        if (!m_MouseIsInWindowRect)
        {
            m_MouseIsInWindowRect = true;
            SetCursorIcon(IDC_ARROW);
        }

        // Make sure we know when the cursor leaves the window
        TRACKMOUSEEVENT ev{ sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_WindowHandle, 0 };
        TrackMouseEvent(&ev);
    }
    else if(a_Msg.message == WM_MOUSELEAVE)
    {
        m_MouseIsInWindowRect = false;
    }
}

bool tabi::InputHandler::IsButtonDownInternal(unsigned a_Button, bool* a_DownLastFrame) const
{
#if _DEBUG
    TABI_ASSERT(IsBound(a_Button), "Trying to get button state for an unbound button");
#endif

    if (a_DownLastFrame)
    {
        *a_DownLastFrame = m_InputMap.GetBoolPrevious(a_Button);
    }

    return m_InputMap.GetBool(a_Button);
}

float tabi::InputHandler::GetAxisValueInternal(unsigned int a_Axis, float* a_Delta) const
{
    a_Axis += UserButtonAxisOffset;

    float pos = 0.0f;

    if (a_Axis != static_cast<unsigned>(EMouse::Wheel) + UserButtonAxisOffset)
    {
#if _DEBUG
        TABI_ASSERT(IsBound(a_Axis), "Trying to get button state for an unbound axis");
#endif
        pos = m_InputMap.GetFloat(a_Axis);
    }

    if (a_Axis == static_cast<unsigned>(EMouse::MouseX) + UserButtonAxisOffset)
    {
        pos *= static_cast<float>(m_WindowWidth);
    }
    else if (a_Axis == static_cast<unsigned>(EMouse::MouseY) + UserButtonAxisOffset)
    {
        pos *= static_cast<float>(m_WindowHeight);
    }

    if (a_Delta)
    {
        if (a_Axis == static_cast<unsigned>(EMouse::MouseX) + UserButtonAxisOffset)
        {
            *a_Delta = static_cast<float>(m_MouseDeltaX) / static_cast<float>(m_WindowWidth);
        }
        else if (a_Axis == static_cast<unsigned>(EMouse::MouseY) + UserButtonAxisOffset)
        {
            *a_Delta = static_cast<float>(m_MouseDeltaY) / static_cast<float>(m_WindowHeight);
        }
        else if(a_Axis == static_cast<unsigned>(EMouse::Wheel) + UserButtonAxisOffset)
        {
            *a_Delta = m_MouseWheelDeltaY;
        }
        else
        {
            *a_Delta = m_InputMap.GetFloatDelta(a_Axis);
        }
    }

    return pos;
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

void tabi::InputHandler::SetCursorIcon(LPTSTR a_CursorIcon) const
{
    ::SetCursor(::LoadCursor(NULL, a_CursorIcon));
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
