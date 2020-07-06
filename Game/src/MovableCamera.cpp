#include "MovableCamera.h"

#include <Enums/EMouse.h>
#include <Enums/EKeyboard.h>
#include <Enums/EController.h>

#include <Math/TabiMath.h>

MovableCamera::MovableCamera()
    : m_Camera(tabi::make_shared<tabi::Camera>())
    , m_DeltaTime(0.0f)
{
    // Keyboard and mouse
    tabi::InputManager::BindButton(tabi::EMouse::Left, this, BUTTON_CALLBACK(*this, MovableCamera::MoveUp));
    tabi::InputManager::BindButton(tabi::EKeyboard::LSHIFT, this, BUTTON_CALLBACK(*this, MovableCamera::MoveUp));
    tabi::InputManager::BindButton(tabi::EMouse::Right, this, BUTTON_CALLBACK(*this, MovableCamera::MoveDown));
    tabi::InputManager::BindButton(tabi::EKeyboard::LCTRL, this, BUTTON_CALLBACK(*this, MovableCamera::MoveDown));
    tabi::InputManager::BindButton(tabi::EKeyboard::W, this, BUTTON_CALLBACK(*this, MovableCamera::MoveForward));
    tabi::InputManager::BindButton(tabi::EKeyboard::S, this, BUTTON_CALLBACK(*this, MovableCamera::MoveBackwards));
    tabi::InputManager::BindButton(tabi::EKeyboard::A, this, BUTTON_CALLBACK(*this, MovableCamera::MoveLeft));
    tabi::InputManager::BindButton(tabi::EKeyboard::D, this, BUTTON_CALLBACK(*this, MovableCamera::MoveRight));
    tabi::InputManager::BindAxis(tabi::EMouse::MouseX, this, AXIS_CALLBACK(*this, MovableCamera::RotateHorizontal));
    tabi::InputManager::BindAxis(tabi::EMouse::MouseY, this, AXIS_CALLBACK(*this, MovableCamera::RotateVertical));
    
    // Controller
    tabi::InputManager::BindButton(tabi::EController::R1, this, BUTTON_CALLBACK(*this, MovableCamera::MoveUp));
    tabi::InputManager::BindButton(tabi::EController::R2, this, BUTTON_CALLBACK(*this, MovableCamera::MoveDown));
    tabi::InputManager::BindAxis(tabi::EController::LeftStickX, this, AXIS_CALLBACK(*this, MovableCamera::MoveRightController));
    tabi::InputManager::BindAxis(tabi::EController::LeftStickY, this, AXIS_CALLBACK(*this, MovableCamera::MoveForwardController));
    tabi::InputManager::BindAxis(tabi::EController::RightStickX, this, AXIS_CALLBACK(*this, MovableCamera::RotateHorizontalController));
    tabi::InputManager::BindAxis(tabi::EController::RightStickY, this, AXIS_CALLBACK(*this, MovableCamera::RotateVerticalController));
}

void MovableCamera::MoveUp(bool)
{
    m_Camera->MoveBy(m_Camera->GetUp() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveDown(bool)
{
    m_Camera->MoveBy(-m_Camera->GetUp() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveLeft(bool)
{
    m_Camera->MoveBy(-m_Camera->GetRight() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveRight(bool)
{
    m_Camera->MoveBy(m_Camera->GetRight() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveForward(bool)
{
    m_Camera->MoveBy(m_Camera->GetForward() * m_Speed * m_DeltaTime);
}

void MovableCamera::MoveBackwards(bool)
{
    m_Camera->MoveBy(m_Camera->GetForward() * -m_Speed * m_DeltaTime);
}

void MovableCamera::RotateHorizontal(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Curr);
    if (std::abs(a_Delta) > FLT_EPSILON)
    {
        m_Camera->RotateBy(tabi::vec3(0, m_MouseSensitivity * m_DeltaTime * a_Delta, 0));
    }
}

void MovableCamera::RotateVertical(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Curr);
    if (std::abs(a_Delta) > FLT_EPSILON)
    {
        m_Camera->RotateBy(tabi::vec3(m_MouseSensitivity * m_DeltaTime * -a_Delta, 0, 0));
        ConstrainRotation();
    }
}

void MovableCamera::MoveForwardController(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Delta);
    if (std::abs(a_Curr) > FLT_EPSILON)
    {
        m_Camera->MoveBy(m_Camera->GetForward() * -m_Speed * a_Curr * m_DeltaTime);
    }
}

void MovableCamera::MoveRightController(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Delta);
    if (std::abs(a_Curr) > FLT_EPSILON)
    {
        m_Camera->MoveBy(m_Camera->GetRight() * m_Speed * a_Curr * m_DeltaTime);
    }
}

void MovableCamera::RotateHorizontalController(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Delta);
    if (std::abs(a_Curr) > 0.0f)
    {
        m_Camera->RotateBy(tabi::vec3(0, m_ControllerSensitivity * m_DeltaTime * a_Curr, 0));
    }
}

void MovableCamera::RotateVerticalController(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Delta);
    if (std::abs(a_Curr) > 0.0f)
    {
        m_Camera->RotateBy(tabi::vec3(-m_ControllerSensitivity * m_DeltaTime * a_Curr, 0, 0));
        ConstrainRotation();
    }
}

void MovableCamera::Update(float a_DeltaTime)
{
    m_DeltaTime = a_DeltaTime;
}

void MovableCamera::ConstrainRotation()
{
    auto rot = m_Camera->GetRotation();
    if (rot.x > tabi::DegToRad(89.0f))
    {
        m_Camera->RotateTo(tabi::vec3(tabi::DegToRad(89.0f), rot.y, rot.z));
    }
    else if (rot.x < tabi::DegToRad(-89.0f))
    {
        m_Camera->RotateTo(tabi::vec3(tabi::DegToRad(-89.0f), rot.y, rot.z));
    }
}
