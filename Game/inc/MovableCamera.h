#pragma once

#include <TabiPointers.h>
#include <Camera.h>

#include <InputManager.h>

class MovableCamera
{
public:
    MovableCamera();

    void MoveUp         (tabi::ButtonEvent);
    void MoveDown       (tabi::ButtonEvent);
    void MoveLeft       (tabi::ButtonEvent);
    void MoveRight      (tabi::ButtonEvent);
    void MoveForward    (tabi::ButtonEvent);
    void MoveBackwards  (tabi::ButtonEvent);

    void RotateHorizontal(tabi::AxisEvent a_Event);
    void RotateVertical(tabi::AxisEvent a_Event);

    void MoveForwardController      (tabi::AxisEvent a_Event);
    void MoveRightController        (tabi::AxisEvent a_Event);
    void RotateHorizontalController (tabi::AxisEvent a_Event);
    void RotateVerticalController   (tabi::AxisEvent a_Event);

    void Update(float a_DeltaTime);
    

private:
    void ConstrainRotation();

public:
    tabi::shared_ptr<tabi::Camera> m_Camera;

    float m_DeltaTime;
    const float m_Speed = 10.0f;
    const float m_MouseSensitivity = 100.0f;
    const float m_ControllerSensitivity = 10.0f;
};