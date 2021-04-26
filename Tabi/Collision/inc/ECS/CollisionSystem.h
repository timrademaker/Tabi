#pragma once

#include <ISystem.h>

namespace tabi
{
    class ColliderComponent;

    class CollisionSystem : public ISystem
    {
    public:
        CollisionSystem(tabi::ComponentManager* a_ComponentManager)
            : ISystem(a_ComponentManager)
        {
        }
        CollisionSystem(ISystem&) = delete;
        CollisionSystem(const ISystem&) = delete;
        virtual ~CollisionSystem() override = default;

        virtual void OnUpdate(float a_DeltaTime) override final;

    private:
        void CheckColliderOverlap(const tabi::Entity a_Entity1, tabi::ColliderComponent& a_Collider1, const tabi::Entity a_Entity2, tabi::ColliderComponent& a_Collider2);

    private:
        /** All pairs of entities that were overlapping during the previous update */
        tabi::map<tabi::Entity, tabi::set<tabi::Entity>> m_OverlappingEntities;
    };
}