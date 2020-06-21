#include "MovableCamera.h"

MovableCamera::MovableCamera()
    : m_Camera(tabi::make_shared<tabi::Camera>())
    , m_DeltaTime(0.0f)
{
    tabi::InputManager::BindButton(tabi::EMouse::Left, this, BUTTON_CALLBACK(*this, MovableCamera::MoveUp));
    tabi::InputManager::BindButton(tabi::EMouse::Right, this, BUTTON_CALLBACK(*this, MovableCamera::MoveDown));
    tabi::InputManager::BindButton(tabi::EMouse::Mouse4, this, BUTTON_CALLBACK(*this, MovableCamera::MoveForward));
    tabi::InputManager::BindButton(tabi::EMouse::Mouse5, this, BUTTON_CALLBACK(*this, MovableCamera::MoveBackwards));
    tabi::InputManager::BindAxis(tabi::EMouse::MouseX, this, AXIS_CALLBACK(*this, MovableCamera::RotateHorizontal));
    tabi::InputManager::BindAxis(tabi::EMouse::MouseY, this, AXIS_CALLBACK(*this, MovableCamera::RotateVertical));
}

void MovableCamera::MoveUp(bool)
{
    m_Camera->MoveBy(tabi::vec3(0, m_Speed * m_DeltaTime, 0));
}

void MovableCamera::MoveDown(bool)
{
    m_Camera->MoveBy(tabi::vec3(0, -m_Speed * m_DeltaTime, 0));
}

void MovableCamera::MoveLeft(bool)
{
    m_Camera->MoveBy(tabi::vec3(-m_Speed * m_DeltaTime, 0, 0));
}

void MovableCamera::MoveRight(bool)
{
    m_Camera->MoveBy(tabi::vec3(m_Speed * m_DeltaTime, 0, 0));
}

void MovableCamera::MoveForward(bool)
{
    m_Camera->MoveBy(tabi::vec3(0, 0, m_Speed * m_DeltaTime));
}

void MovableCamera::MoveBackwards(bool)
{
    m_Camera->MoveBy(tabi::vec3(0, 0, -m_Speed * m_DeltaTime));
}

void MovableCamera::RotateVertical(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Curr);
    m_Camera->RotateBy(tabi::vec3(m_Sensitivity * m_DeltaTime * a_Delta, 0, 0));
}

void MovableCamera::RotateHorizontal(float a_Curr, float a_Delta)
{
    TABI_UNUSED(a_Curr);
    m_Camera->RotateBy(tabi::vec3(0, m_Sensitivity * m_DeltaTime * a_Delta, 0));
}

void MovableCamera::Update(float a_DeltaTime)
{
    m_DeltaTime = a_DeltaTime;
}