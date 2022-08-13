#pragma once

#include <Camera.h>

#include <InputManager.h>

class MovableCamera : public tabi::Camera
{
public:
    MovableCamera(float a_AspectRatio);

    void MoveUp         (tabi::ButtonDownEvent);
    void MoveDown       (tabi::ButtonDownEvent);
    void MoveLeft       (tabi::ButtonDownEvent);
    void MoveRight      (tabi::ButtonDownEvent);
    void MoveForward    (tabi::ButtonDownEvent);
    void MoveBackwards  (tabi::ButtonDownEvent);

    void RotateHorizontal   (tabi::AxisEvent a_Event);
    void RotateVertical     (tabi::AxisEvent a_Event);

    void MoveForwardController      (tabi::AxisEvent a_Event);
    void MoveRightController        (tabi::AxisEvent a_Event);
    void RotateHorizontalController (tabi::AxisEvent a_Event);
    void RotateVerticalController   (tabi::AxisEvent a_Event);

    void Update(float a_DeltaTime);

public:
    float m_DeltaTime;
    const float m_Speed = 10.0f;
    const float m_MouseSensitivity = 100.0f;
    const float m_ControllerSensitivity = 10.0f;
};