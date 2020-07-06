#pragma once

#include <TabiPointers.h>
#include <Camera.h>

#include <InputManager.h>

class MovableCamera
{
public:
    MovableCamera();

    void MoveUp(bool);
    void MoveDown(bool);
    void MoveLeft(bool);
    void MoveRight(bool);
    void MoveForward(bool);
    void MoveBackwards(bool);

    void RotateHorizontal(float a_Curr, float a_Delta);
    void RotateVertical(float a_Curr, float a_Delta);

    void MoveForwardController(float a_Curr, float a_Delta);
    void MoveRightController(float a_Curr, float a_Delta);
    void RotateHorizontalController(float a_Curr, float a_Delta);
    void RotateVerticalController(float a_Curr, float a_Delta);

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