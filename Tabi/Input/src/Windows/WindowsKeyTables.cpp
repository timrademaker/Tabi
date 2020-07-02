#include <Windows/WindowsInputHandler.h>

#include "Enums/EMouse.h"
#include "Enums/EKeyboard.h"
#include "Enums/EController.h"

#include <TabiMacros.h>

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
    {EMouse::MouseX, gainput::MouseButton::MouseAxisX},
    {EMouse::MouseY, gainput::MouseButton::MouseAxisY},
    {EMouse::WheelUp, gainput::MouseButton::MouseButtonWheelUp},
    {EMouse::WheelDown, gainput::MouseButton::MouseButtonWheelDown}
};

tabi::unordered_map<EKeyboard, unsigned int> tabi::InputHandler::ms_KeyboardTable =
{
    // Letters
    {EKeyboard::A, gainput::Key::KeyA},
    {EKeyboard::B, gainput::Key::KeyB},
    {EKeyboard::C, gainput::Key::KeyC},
    {EKeyboard::D, gainput::Key::KeyD},
    {EKeyboard::E, gainput::Key::KeyE},
    {EKeyboard::F, gainput::Key::KeyF},
    {EKeyboard::G, gainput::Key::KeyG},
    {EKeyboard::H, gainput::Key::KeyH},
    {EKeyboard::I, gainput::Key::KeyI},
    {EKeyboard::J, gainput::Key::KeyJ},
    {EKeyboard::K, gainput::Key::KeyK},
    {EKeyboard::L, gainput::Key::KeyL},
    {EKeyboard::M, gainput::Key::KeyM},
    {EKeyboard::N, gainput::Key::KeyN},
    {EKeyboard::O, gainput::Key::KeyO},
    {EKeyboard::P, gainput::Key::KeyP},
    {EKeyboard::Q, gainput::Key::KeyQ},
    {EKeyboard::R, gainput::Key::KeyR},
    {EKeyboard::S, gainput::Key::KeyS},
    {EKeyboard::T, gainput::Key::KeyT},
    {EKeyboard::U, gainput::Key::KeyU},
    {EKeyboard::V, gainput::Key::KeyV},
    {EKeyboard::W, gainput::Key::KeyW},
    {EKeyboard::X, gainput::Key::KeyX},
    {EKeyboard::Y, gainput::Key::KeyY},
    {EKeyboard::Z, gainput::Key::KeyZ},
    // Modifiers
    {EKeyboard::LCTRL, gainput::Key::KeyCtrlL},
    {EKeyboard::RCTRL, gainput::Key::KeyCtrlR},
    {EKeyboard::LALT, gainput::Key::KeyAltL},
    {EKeyboard::RALT, gainput::Key::KeyAltR},
    {EKeyboard::LSHIFT, gainput::Key::KeyShiftL},
    {EKeyboard::RSHIFT, gainput::Key::KeyShiftR},
    {EKeyboard::ENTER, gainput::Key::KeyReturn},
    {EKeyboard::BACKSPACE, gainput::Key::KeyBackSpace},
    {EKeyboard::ESCAPE, gainput::Key::KeyEscape},
    {EKeyboard::SPACE, gainput::Key::KeySpace},
    {EKeyboard::TAB, gainput::Key::KeyTab},
    // Arrows
    {EKeyboard::ARROW_UP, gainput::Key::KeyUp},
    {EKeyboard::ARROW_DOWN, gainput::Key::KeyDown},
    {EKeyboard::ARROW_LEFT, gainput::Key::KeyLeft},
    {EKeyboard::ARROW_RIGHT, gainput::Key::KeyRight},
    // Numbers
    {EKeyboard::KEY0, gainput::Key::Key0},
    {EKeyboard::KEY1, gainput::Key::Key1},
    {EKeyboard::KEY2, gainput::Key::Key2},
    {EKeyboard::KEY3, gainput::Key::Key3},
    {EKeyboard::KEY4, gainput::Key::Key4},
    {EKeyboard::KEY5, gainput::Key::Key5},
    {EKeyboard::KEY6, gainput::Key::Key6},
    {EKeyboard::KEY7, gainput::Key::Key7},
    {EKeyboard::KEY8, gainput::Key::Key8},
    {EKeyboard::KEY9, gainput::Key::Key9},
    // Numpad
    {EKeyboard::KP_0, gainput::Key::KeyKpInsert},
    {EKeyboard::KP_1, gainput::Key::KeyKpEnd},
    {EKeyboard::KP_2, gainput::Key::KeyKpDown},
    {EKeyboard::KP_3, gainput::Key::KeyKpPageDown},
    {EKeyboard::KP_4, gainput::Key::KeyKpLeft},
    {EKeyboard::KP_5, gainput::Key::KeyKpBegin},
    {EKeyboard::KP_6, gainput::Key::KeyKpRight},
    {EKeyboard::KP_7, gainput::Key::KeyKpHome},
    {EKeyboard::KP_8, gainput::Key::KeyKpUp},
    {EKeyboard::KP_9, gainput::Key::KeyKpPageUp},
    {EKeyboard::KP_SLASH, gainput::Key::KeyKpDivide},
    {EKeyboard::KP_ASTERISK, gainput::Key::KeyKpMultiply},
    {EKeyboard::KP_PLUS, gainput::Key::KeyKpAdd},
    {EKeyboard::KP_MINUS, gainput::Key::KeyKpSubtract},
    {EKeyboard::KP_DOT, gainput::Key::KeyKpDelete},
    // Function keys
    {EKeyboard::F1, gainput::Key::KeyF1},
    {EKeyboard::F2, gainput::Key::KeyF2},
    {EKeyboard::F3, gainput::Key::KeyF3},
    {EKeyboard::F4, gainput::Key::KeyF4},
    {EKeyboard::F5, gainput::Key::KeyF5},
    {EKeyboard::F6, gainput::Key::KeyF6},
    {EKeyboard::F7, gainput::Key::KeyF7},
    {EKeyboard::F8, gainput::Key::KeyF8},
    {EKeyboard::F9, gainput::Key::KeyF9},
    {EKeyboard::F10, gainput::Key::KeyF10},
    {EKeyboard::F11, gainput::Key::KeyF11},
    {EKeyboard::F12, gainput::Key::KeyF12}
};

tabi::unordered_map<EController, unsigned int> tabi::InputHandler::ms_ControllerTable =
{
    // D-Pad
    {EController::DPadLeft, gainput::PadButton::PadButtonLeft},
    {EController::DPadRight, gainput::PadButton::PadButtonRight},
    {EController::DPadUp, gainput::PadButton::PadButtonUp},
    {EController::DPadDown, gainput::PadButton::PadButtonDown},
    // Face buttons
    {EController::FaceLeft, gainput::PadButton::PadButtonX},
    {EController::FaceRight, gainput::PadButton::PadButtonB},
    {EController::FaceUp, gainput::PadButton::PadButtonY},
    {EController::FaceDown, gainput::PadButton::PadButtonA},
    // Special
    {EController::SpecialLeft, gainput::PadButton::PadButtonSelect},
    {EController::SpecialRight, gainput::PadButton::PadButtonStart},
    {EController::Home, gainput::PadButton::PadButtonHome},
    // Shoulder buttons/bumpers
    {EController::L1, gainput::PadButton::PadButtonL1},
    {EController::L2, gainput::PadButton::PadButtonL3},
    {EController::L3, gainput::PadButton::PadButtonL3},
    {EController::R1, gainput::PadButton::PadButtonR1},
    {EController::R2, gainput::PadButton::PadButtonR2},
    {EController::R3, gainput::PadButton::PadButtonR3},
    // Sticks
    {EController::LeftStickX, gainput::PadButton::PadButtonLeftStickX},
    {EController::LeftStickY, gainput::PadButton::PadButtonLeftStickY},
    {EController::RightStickX, gainput::PadButton::PadButtonRightStickX},
    {EController::RightStickY, gainput::PadButton::PadButtonRightStickY},
    // Gyroscope
    {EController::GyroscopeX, gainput::PadButton::PadButtonGyroscopeX},
    {EController::GyroscopeY, gainput::PadButton::PadButtonGyroscopeY},
    {EController::GyroscopeZ, gainput::PadButton::PadButtonGyroscopeZ},
    // Magnetic field
    {EController::MagneticFieldX, gainput::PadButton::PadButtonMagneticFieldX},
    {EController::MagneticFieldY, gainput::PadButton::PadButtonMagneticFieldY},
    {EController::MagneticFieldZ, gainput::PadButton::PadButtonMagneticFieldZ}
};