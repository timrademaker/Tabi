#include "Windows/WindowsInputHandler.h"

#include "Enums/EMouse.h"
#include "Enums/EInputDevice.h"

#include <Logging.h>

#include <TabiMacros.h>

#include <IRenderer.h>

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

tabi::unordered_map<tabi::EMouse, unsigned int> tabi::InputHandler::ms_MouseTable =
{
    {EMouse::Left, gainput::MouseButton::MouseButtonLeft},
    {EMouse::Right, gainput::MouseButton::MouseButtonRight},
    {EMouse::Middle, gainput::MouseButton::MouseButtonMiddle},
    {EMouse::Mouse4, gainput::MouseButton::MouseButton5},
    {EMouse::Mouse5, gainput::MouseButton::MouseButton6},
    {EMouse::MouseX, gainput::MouseButton::MouseButtonRight},
    {EMouse::MouseY, gainput::MouseButton::MouseButtonRight},
    {EMouse::WheelUp, gainput::MouseButton::MouseButtonWheelUp},
    {EMouse::WheelDown, gainput::MouseButton::MouseButtonWheelDown}
};

tabi::unordered_map<EKeyboard, unsigned int> tabi::InputHandler::ms_KeyboardTable = {};
tabi::unordered_map<EController, unsigned int> tabi::InputHandler::ms_ControllerTable = {};


tabi::InputHandler::InputHandler()
    : m_InputMap(m_GaInputManager)
{
    unsigned int width;
    unsigned int height;
    tabi::graphics::IRenderer::GetInstance().GetWindowDimensions(width, height);

    m_GaInputManager.SetDisplaySize(width, height);

    //m_InputDeviceTable[EInputDevice::Controller] = m_GaInputManager.CreateDevice<gainput::InputDevicePad>();
    m_InputDeviceTable[EInputDevice::Keyboard] = m_GaInputManager.CreateDevice<gainput::InputDeviceKeyboard>();
    m_InputDeviceTable[EInputDevice::Mouse] = m_GaInputManager.CreateDevice<gainput::InputDeviceMouse>();
}


void tabi::InputHandler::Update()
{
    m_GaInputManager.Update();
}

void tabi::InputHandler::BindButton(unsigned int a_Button)
{
    EInputDevice deviceType = DetermineDeviceType(a_Button);
    auto device = ConvertDeviceType(deviceType);
    unsigned int convertedButton = ConvertButton(a_Button);

    m_InputMap.MapBool(a_Button, device, convertedButton);
}

void tabi::InputHandler::BindAxis(unsigned int a_Axis)
{
    EInputDevice deviceType = DetermineDeviceType(a_Axis);
    auto device = ConvertDeviceType(deviceType);
    unsigned int convertedButton = ConvertButton(a_Axis);

    m_InputMap.MapFloat(a_Axis, device, convertedButton);
}

bool tabi::InputHandler::IsButtonDown(unsigned int a_Button)
{
    if (IsBound(a_Button))
    {
        return m_InputMap.GetBool(a_Button);
    }
    else
    {
        return false;
    }
}

float tabi::InputHandler::GetAxisValue(unsigned int a_Axis)
{
    if (IsBound(a_Axis))
    {
        return m_InputMap.GetFloat(a_Axis);
    }
    else
    {
        return 0.0f;
    }
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
    if (a_Button & static_cast<unsigned>(EInputDevice::Mouse))
    {
        return EInputDevice::Mouse;
    }
    else if (a_Button & static_cast<unsigned>(EInputDevice::Keyboard))
    {
        return EInputDevice::Keyboard;
    }
    else if (a_Button & static_cast<unsigned>(EInputDevice::Controller))
    {
        return EInputDevice::Controller;
    }

    logger::TabiWarn("Unable to determine device type for button " + tabi::to_string(a_Button));
    return EInputDevice();
}

bool tabi::InputHandler::IsBound(unsigned int a_Button)
{
    if (m_InputMap.IsMapped(a_Button))
    {
        return true;
    }
    else
    {
        logger::TabiWarn("Trying to get button state for an unbound button: " + tabi::to_string(a_Button));
        return false;
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