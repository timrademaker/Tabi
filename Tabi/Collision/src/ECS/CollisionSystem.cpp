#include "ECS/CollisionSystem.h"

#include "ECS/ColliderComponent.h"
#include "GJK.h"

#include <ComponentManager.h>
#include <Components/Transform.h>

void tabi::CollisionSystem::OnUpdate(float a_DeltaTime)
{
    TABI_UNUSED(a_DeltaTime);

    for (const auto& ent1 : m_Entities)
    {
        const auto& transform1 = m_ComponentManager->GetComponent<tabi::Transform>(ent1);
        auto& collider1 = m_ComponentManager->GetComponent<tabi::ColliderComponent>(ent1);
        collider1.m_Collider->SetWorldTransfrom(transform1);
        
        for (const auto& ent2 : m_Entities)
        {
            if (ent1 == ent2)
            {
                continue;
            }

            const auto& transform2 = m_ComponentManager->GetComponent<tabi::Transform>(ent2);
            auto& collider2 = m_ComponentManager->GetComponent<tabi::ColliderComponent>(ent2);
            collider2.m_Collider->SetWorldTransfrom(transform2);

            CheckColliderOverlap(ent1, collider1, ent2, collider2);
        }
    }
}

void tabi::CollisionSystem::CheckColliderOverlap(const tabi::Entity a_Entity1, tabi::ColliderComponent& a_Collider1, const tabi::Entity a_Entity2, tabi::ColliderComponent& a_Collider2)
{
    const tabi::Entity& keyEntity = a_Entity1 < a_Entity2 ? a_Entity1 : a_Entity2;
    const tabi::Entity& valueEntity = a_Entity1 < a_Entity2 ? a_Entity2 : a_Entity1;

    auto& previouslyOverlappingEntities = m_OverlappingEntities[keyEntity];
    bool entitiesWereOverlappingPreviously = false;
    
    if (previouslyOverlappingEntities.find(valueEntity) != previouslyOverlappingEntities.end())
    {
        // Colliders weren't overlapping in the previous frame
        entitiesWereOverlappingPreviously = true;
    }

    if (CheckColliderOverlapBroadPhase(a_Collider1.m_Collider.get(), a_Collider2.m_Collider.get())
        && GJK::CollidersAreOverlapping(a_Collider1.m_Collider.get(), a_Collider2.m_Collider.get()))
    {
        if (!entitiesWereOverlappingPreviously)
        {
            // Broadcast event for the first collider
            {
                tabi::OverlapInfo oi;
                oi.m_OtherEntity = a_Entity2;
                oi.m_OverlappedCollider = a_Collider2.m_Collider;
                a_Collider1.m_OnColliderBeginOverlap.Broadcast(oi);
            }

            // Broadcast event for the second collider
            {
                tabi::OverlapInfo oi;
                oi.m_OtherEntity = a_Entity1;
                oi.m_OverlappedCollider = a_Collider1.m_Collider;
                a_Collider2.m_OnColliderBeginOverlap.Broadcast(oi);
            }

            previouslyOverlappingEntities.insert(valueEntity);
        }
    }
    else if(entitiesWereOverlappingPreviously)
    {
        previouslyOverlappingEntities.erase(valueEntity);

        // Broadcast event for the first collider
        {
            tabi::OverlapInfo oi;
            oi.m_OtherEntity = a_Entity2;
            oi.m_OverlappedCollider = a_Collider2.m_Collider;
            a_Collider1.m_OnColliderEndOverlap.Broadcast(oi);
        }

        // Broadcast event for the second collider
        {
            tabi::OverlapInfo oi;
            oi.m_OtherEntity = a_Entity1;
            oi.m_OverlappedCollider = a_Collider1.m_Collider;
            a_Collider2.m_OnColliderEndOverlap.Broadcast(oi);
        }
    }
}

bool tabi::CollisionSystem::CheckColliderOverlapBroadPhase(const tabi::ICollider* a_Collider1, const tabi::ICollider* a_Collider2) const
{
    const float sphereRadii = a_Collider1->GetBroadPhaseRadius() + a_Collider2->GetBroadPhaseRadius();
    const float squaredDistanceBetweenColliders = (a_Collider1->GetPosition() - a_Collider2->GetPosition()).LengthSquared();

    return squaredDistanceBetweenColliders <= (sphereRadii * sphereRadii);
}
