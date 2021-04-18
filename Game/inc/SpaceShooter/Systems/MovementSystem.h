#pragma once

#include "ISystem.h"

namespace SpaceShooter
{
    class MovementSystem : public tabi::ISystem
    {
    public:
        MovementSystem(tabi::ComponentManager* a_ComponentManager)
            : ISystem(a_ComponentManager)
        {
        }

        virtual void OnUpdate(float a_DeltaTime) override;
    };
}