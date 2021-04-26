#pragma once

#include "Colliders/ICollider.h"

#include <Entity.h>

#include <TabiPointers.h>
#include <TabiEvent.h>

namespace tabi
{
    struct OverlapInfo
    {
        tabi::Entity m_OtherEntity;
        tabi::shared_ptr<tabi::ICollider> m_OverlappedCollider;
    };

    DECLARE_EVENT(OnColliderBeginOverlap, OverlapInfo);
    DECLARE_EVENT(OnColliderEndOverlap, OverlapInfo);

    class ColliderComponent
    {
    public:
        ColliderComponent();
        ColliderComponent(tabi::shared_ptr<tabi::ICollider> a_Collider);
        ~ColliderComponent() = default;

    public:
        tabi::shared_ptr<tabi::ICollider> m_Collider;

        OnColliderBeginOverlap m_OnColliderBeginOverlap;
        OnColliderEndOverlap m_OnColliderEndOverlap;
    };
}
