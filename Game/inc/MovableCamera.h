#pragma once

#include <TabiPointers.h>
#include <Camera.h>

#include <Enums/EMouse.h>
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

    void Update(float a_DeltaTime);
    

    tabi::shared_ptr<tabi::Camera> m_Camera;

    float m_DeltaTime;
    float m_Speed = 10.0f;
};