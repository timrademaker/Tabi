#pragma once

#include <GameBase.h>
#include <Camera.h>
#include <ECS.h>


namespace SpaceShooter
{
    class SpaceShooterGameMode : public tabi::GameBase
    {
    public:
        SpaceShooterGameMode(const char* a_Name, const int a_Width, const int a_Height, const bool a_Vsync)
            : GameBase(a_Name, a_Width, a_Height, a_Vsync), m_Player(nullptr)
        {
        };
        virtual ~SpaceShooterGameMode();

        virtual bool OnInitialize() override;
        virtual void OnUpdate(float a_DeltaTime) override;

    private:
        void OnGameOver();

    private:
        tabi::shared_ptr<tabi::Camera> m_Camera;
        tabi::ECS m_ECS;

        class Player* m_Player;
    };
}
