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

    {EKeyboard::Minus, gainput::Key::KeyMinus},
    {EKeyboard::Equals, gainput::Key::KeyEquals},
    {EKeyboard::BracketLeft, gainput::Key::KeyBracketLeft},
    {EKeyboard::BracketRight, gainput::Key::KeyBracketRight},
    {EKeyboard::Semicolon, gainput::Key::KeySemicolon},
    {EKeyboard::Apostrophe, gainput::Key::KeyApostrophe},
    {EKeyboard::Comma, gainput::Key::KeyComma},
    {EKeyboard::Period, gainput::Key::KeyPeriod},
    {EKeyboard::Slash, gainput::Key::KeySlash},
    {EKeyboard::Backslash, gainput::Key::KeyBackslash},
    {EKeyboard::AccentGrave, gainput::Key::KeyGrave},

    // Modifiers
    {EKeyboard::LeftCtrl, gainput::Key::KeyCtrlL},
    {EKeyboard::RightCtrl, gainput::Key::KeyCtrlR},
    {EKeyboard::LeftAlt, gainput::Key::KeyAltL},
    {EKeyboard::RightAlt, gainput::Key::KeyAltR},
    {EKeyboard::LeftShift, gainput::Key::KeyShiftL},
    {EKeyboard::RightShift, gainput::Key::KeyShiftR},
    {EKeyboard::Enter, gainput::Key::KeyReturn},
    {EKeyboard::Backspace, gainput::Key::KeyBackSpace},
    {EKeyboard::Escape, gainput::Key::KeyEscape},
    {EKeyboard::Space, gainput::Key::KeySpace},
    {EKeyboard::Tab, gainput::Key::KeyTab},
    // Arrows
    {EKeyboard::ArrowUp, gainput::Key::KeyUp},
    {EKeyboard::ArrowDown, gainput::Key::KeyDown},
    {EKeyboard::ArrowLeft, gainput::Key::KeyLeft},
    {EKeyboard::ArrowRight, gainput::Key::KeyRight},
    // Numbers
    {EKeyboard::Key0, gainput::Key::Key0},
    {EKeyboard::Key1, gainput::Key::Key1},
    {EKeyboard::Key2, gainput::Key::Key2},
    {EKeyboard::Key3, gainput::Key::Key3},
    {EKeyboard::Key4, gainput::Key::Key4},
    {EKeyboard::Key5, gainput::Key::Key5},
    {EKeyboard::Key6, gainput::Key::Key6},
    {EKeyboard::Key7, gainput::Key::Key7},
    {EKeyboard::Key8, gainput::Key::Key8},
    {EKeyboard::Key9, gainput::Key::Key9},
    // Numpad
    {EKeyboard::Keypad0, gainput::Key::KeyKpInsert},
    {EKeyboard::Keypad1, gainput::Key::KeyKpEnd},
    {EKeyboard::Keypad2, gainput::Key::KeyKpDown},
    {EKeyboard::Keypad3, gainput::Key::KeyKpPageDown},
    {EKeyboard::Keypad4, gainput::Key::KeyKpLeft},
    {EKeyboard::Keypad5, gainput::Key::KeyKpBegin},
    {EKeyboard::Keypad6, gainput::Key::KeyKpRight},
    {EKeyboard::Keypad7, gainput::Key::KeyKpHome},
    {EKeyboard::Keypad8, gainput::Key::KeyKpUp},
    {EKeyboard::Keypad9, gainput::Key::KeyKpPageUp},
    {EKeyboard::KeypadSlash, gainput::Key::KeyKpDivide},
    {EKeyboard::KeypadAsterisk, gainput::Key::KeyKpMultiply},
    {EKeyboard::KeypadPlus, gainput::Key::KeyKpAdd},
    {EKeyboard::KeypadMinus, gainput::Key::KeyKpSubtract},
    {EKeyboard::KeypadPeriod, gainput::Key::KeyKpDelete},
    {EKeyboard::KeypadEnter, gainput::Key::KeyKpEnter},
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
    {EKeyboard::F12, gainput::Key::KeyF12},

    { EKeyboard::Insert, gainput::Key::KeyInsert },
    { EKeyboard::Delete, gainput::Key::KeyDelete },
    { EKeyboard::Home, gainput::Key::KeyHome },
    { EKeyboard::End, gainput::Key::KeyEnd },
    { EKeyboard::PageUp, gainput::Key::KeyKpPageUp },
    { EKeyboard::PageDown, gainput::Key::KeyKpPageDown },
    { EKeyboard::PrintScreen, gainput::Key::KeyPrint },
    { EKeyboard::ScrollLock, gainput::Key::KeyScrollLock },
    { EKeyboard::Pause, gainput::Key::KeyBreak },
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