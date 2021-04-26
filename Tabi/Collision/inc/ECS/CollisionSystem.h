#pragma once

#include <ISystem.h>

namespace tabi
{
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
        void CheckColliderOverlap(const tabi::Entity a_Entity1, class ColliderComponent& a_Collider1, const tabi::Entity a_Entity2, class ColliderComponent& a_Collider2);

        bool CheckColliderOverlapBroadPhase(const class ICollider* a_Collider1, const class ICollider* a_Collider2) const;

    private:
        /** All pairs of entities that were overlapping during the previous update */
        tabi::map<tabi::Entity, tabi::set<tabi::Entity>> m_OverlappingEntities;
    };
}