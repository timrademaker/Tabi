#include "ECS/ColliderComponent.h"

tabi::ColliderComponent::ColliderComponent()
    : m_Collider(nullptr)
{
}

tabi::ColliderComponent::ColliderComponent(tabi::shared_ptr<tabi::ICollider> a_Collider)
    : m_Collider(a_Collider)
{
}
