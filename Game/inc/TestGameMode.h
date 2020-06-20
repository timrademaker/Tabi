#pragma once

#include  <GameBase.h>
#include <Resources/Mesh.h>

#include "MovableCamera.h"

class TestGameMode : public tabi::GameBase
{
public:
    TestGameMode(const char* a_Name, const int a_Width, const int a_Height, const bool a_Vsync)
    : GameBase(a_Name, a_Width, a_Height, a_Vsync)
    {};
    virtual ~TestGameMode() = default;

    virtual bool OnInitialize() override;
    virtual void OnUpdate(float a_DeltaTime) override;
    virtual void OnRender() override;

private:
    tabi::vector<tabi::shared_ptr<tabi::Mesh>> m_Meshes;
    tabi::shared_ptr<MovableCamera> m_Camera;
};