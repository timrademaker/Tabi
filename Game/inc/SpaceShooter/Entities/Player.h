#pragma once

#include <Entity.h>
#include <InputManager.h>
#include <TabiEvent.h>

namespace tabi
{
    class ECS;
}

namespace SpaceShooter
{
    class Player
    {
        /** The delay on respawning when the player dies */
        static constexpr float s_RespawnDelay = 2.0f;
        /** The number of lives the player starts with */
        static constexpr int s_StartingLives = 3;
        /** The path to the mesh used for the player */
        static constexpr const char* s_PlayerMesh = "Assets/Duck.glb";
        /** The speed at which the player moves */
        static constexpr float s_MovementSpeed = 5.0f;

    public:
        Player(tabi::ECS* a_ECS);
        Player(Player&) = delete;
        Player(const Player&) = delete;

        ~Player() = default;

        void Update(const float a_DeltaTime);

        /* Input callbacks */
        void MoveLeft(tabi::ButtonEvent);
        void MoveRight(tabi::ButtonEvent);
        void MoveUp(tabi::ButtonEvent);
        void MoveDown(tabi::ButtonEvent);

        void Shoot(tabi::ButtonEvent);

    public:
        tabi::Event m_OnGameOver;

    private:
        void SetUpPlayerEntity();
        void SetUpPlayerInput();

        void OnDeath();
        void Respawn();

    private:
        /** The entity representing the player */
        tabi::Entity m_PlayerEntity;

        /** The number of lives the player has left */
        int m_RemainingLives;
        /** The current score of the player */
        int m_Score;

        /** Whether the player is waiting to respawn or not */
        bool m_IsPendingRespawn;
        /** The time the player has to wait until they respawn */
        float m_CurrentRespawnTimer;

        /** The game's ECS */
        tabi::ECS* m_ECS;

        /** The last logged DeltaTime */
        float m_DeltaTime;
    };
}