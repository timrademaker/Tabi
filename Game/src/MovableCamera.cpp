#include "MovableCamera.h"

#include <Enums/EMouse.h>
#include <Enums/EKeyboard.h>
#include <Enums/EController.h>

MovableCamera::MovableCamera(float a_AspectRatio)
    : Camera(a_AspectRatio)
    , m_DeltaTime(0.0f)
{
    // Keyboard and mouse
    tabi::InputManager::BindButton(tabi::EMouse::Left, this, &MovableCamera::MoveUp);
    tabi::InputManager::BindButton(tabi::EKeyboard::LeftShift, this, &MovableCamera::MoveUp);
    tabi::InputManager::BindButton(tabi::EMouse::Right, this, &MovableCamera::MoveDown);
    tabi::InputManager::BindButton(tabi::EKeyboard::LeftCtrl, this, &MovableCamera::MoveDown);
    tabi::InputManager::BindButton(tabi::EKeyboard::W, this, &MovableCamera::MoveForward);
    tabi::InputManager::BindButton(tabi::EKeyboard::S, this, &MovableCamera::MoveBackwards);
    tabi::InputManager::BindButton(tabi::EKeyboard::A, this, &MovableCamera::MoveLeft);
    tabi::InputManager::BindButton(tabi::EKeyboard::D, this, &MovableCamera::MoveRight);
    tabi::InputManager::BindAxis(tabi::EMouse::MouseX, this, &MovableCamera::RotateHorizontal);
    tabi::InputManager::BindAxis(tabi::EMouse::MouseY, this, &MovableCamera::RotateVertical);
    
    // Controller
    tabi::InputManager::BindButton(tabi::EController::R1, this, &MovableCamera::MoveUp);
    tabi::InputManager::BindButton(tabi::EController::R2, this, &MovableCamera::MoveDown);
    tabi::InputManager::BindAxis(tabi::EController::LeftStickX, this, &MovableCamera::MoveRightController);
    tabi::InputManager::BindAxis(tabi::EController::LeftStickY, this, &MovableCamera::MoveForwardController);
    tabi::InputManager::BindAxis(tabi::EController::RightStickX, this, &MovableCamera::RotateHorizontalController);
    tabi::InputManager::BindAxis(tabi::EController::RightStickY, this, &MovableCamera::RotateVerticalController);
}

void MovableCamera::MoveUp(tabi::ButtonDownEvent)
{
    MoveBy(GetUp() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveDown(tabi::ButtonDownEvent)
{
    MoveBy(-GetUp() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveLeft(tabi::ButtonDownEvent)
{
    MoveBy(-GetRight() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveRight(tabi::ButtonDownEvent)
{
    MoveBy(GetRight() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveForward(tabi::ButtonDownEvent)
{
    MoveBy(GetForward() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveBackwards(tabi::ButtonDownEvent)
{
    MoveBy(GetForward() * -m_Speed * m_DeltaTime);
}

void MovableCamera::RotateHorizontal(tabi::AxisEvent a_Event)
{
    if (std::abs(a_Event.m_Delta) > FLT_EPSILON)
    {
        LookAt(GetPosition() + GetForward() + (GetRight() * m_MouseSensitivity * m_DeltaTime * a_Event.m_Delta));
    }
}

void MovableCamera::RotateVertical(tabi::AxisEvent a_Event)
{
    if (std::abs(a_Event.m_Delta) > FLT_EPSILON)
    {
        LookAt(GetPosition() + GetForward() + (GetUp() * m_MouseSensitivity * m_DeltaTime * a_Event.m_Delta));
    }
}

void MovableCamera::MoveForwardController(tabi::AxisEvent a_Event)
{
    if (std::abs(a_Event.m_AxisValue) > FLT_EPSILON)
    {
        MoveBy(GetForward() * m_Speed * a_Event.m_AxisValue * m_DeltaTime);
    }
}

void MovableCamera::MoveRightController(tabi::AxisEvent a_Event)
{
    if (std::abs(a_Event.m_AxisValue) > FLT_EPSILON)
    {
        MoveBy(GetRight() * m_Speed * a_Event.m_AxisValue * m_DeltaTime);
    }
}

void MovableCamera::RotateHorizontalController(tabi::AxisEvent a_Event)
{
    if (std::abs(a_Event.m_AxisValue) > FLT_EPSILON)
    {
        LookAt(GetPosition() + GetForward() + (GetRight() * m_ControllerSensitivity * m_DeltaTime * a_Event.m_AxisValue));
    }
}

void MovableCamera::RotateVerticalController(tabi::AxisEvent a_Event)
{
    if (std::abs(a_Event.m_AxisValue) > FLT_EPSILON)
    {
        LookAt(GetPosition() + GetForward() + (GetUp() * -m_ControllerSensitivity * m_DeltaTime * a_Event.m_AxisValue));
    }
}

void MovableCamera::Update(float a_DeltaTime)
{
    m_DeltaTime = a_DeltaTime;
}
