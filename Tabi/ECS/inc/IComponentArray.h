#pragma once

namespace tabi
{
    class Entity;

    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;

        virtual void OnEntityDestroyed(const Entity& a_Entity) = 0;
    };
}
