#pragma once

#include "Colliders/ICollider.h"

#include <Entity.h>

#include <TabiPointers.h>
#include <TabiEvent.h>

namespace tabi
{
    /** Struct containing info about an overlap */
    struct OverlapInfo
    {
        tabi::Entity m_OtherEntity;
        tabi::shared_ptr<tabi::ICollider> m_OverlappedCollider;
    };

    class ColliderComponent
    {
        DECLARE_EVENT(OnColliderBeginOverlap, OverlapInfo);
        DECLARE_EVENT(OnColliderEndOverlap, OverlapInfo);

    public:
        ColliderComponent();
        ColliderComponent(tabi::shared_ptr<tabi::ICollider> a_Collider);
        ~ColliderComponent() = default;

    public:
        tabi::shared_ptr<tabi::ICollider> m_Collider;

        /** Called when two colliders begin overlapping. Takes a parameter of type tabi::OverlapInfo. */
        OnColliderBeginOverlap m_OnColliderBeginOverlap;
        /** Called when two colliders stop overlapping. Takes a parameter of type tabi::OverlapInfo. */
        OnColliderEndOverlap m_OnColliderEndOverlap;
    };
}
