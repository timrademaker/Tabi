#pragma once

#include <ISystem.h>

namespace tabi
{
    class CollisionSystem : public ISystem
    {
    public:
        CollisionSystem(tabi::ComponentManager* a_ComponentManager);
        CollisionSystem(ISystem&) = delete;
        CollisionSystem(const ISystem&) = delete;
        virtual ~CollisionSystem() override = default;

        virtual void OnUpdate(float a_DeltaTime) override final;

    private:
        /**
         * Check if the colldiers of two entities overlap
         * @param a_Entity1 The entity to check for overlap with a_Collider2
         * @param a_Collider1 The collider owned by a_Entity1
         * @param a_Entity2 The entity to check for overlap with a_Collider1
         * @param a_Collider2 The collider owned by a_Entity2
         */
        void CheckColliderOverlap(const tabi::Entity& a_Entity1, class ColliderComponent& a_Collider1, const tabi::Entity& a_Entity2, class ColliderComponent& a_Collider2);

        /**
         * Broad phase collision check for two colliders
         * @param a_Collider1 The collider that should be checked for possible overlap with a_Collider2
         * @param a_Collider2 The collider that should be checked for possible overlap with a_Collider1
         * @return True if the two colliders could be overlapping
         */
        bool CheckColliderOverlapBroadPhase(const class ICollider& a_Collider1, const class ICollider& a_Collider2) const;

    private:
        /** All pairs of entities that were overlapping during the previous update */
        tabi::map<tabi::Entity, tabi::set<tabi::Entity>> m_OverlappingEntities;
    };
}
