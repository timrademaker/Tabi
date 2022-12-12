#include "ECS/StaticMeshComponent.h"

#include <IDevice.h>

tabi::StaticMeshComponent::~StaticMeshComponent()
{
    if (m_MeshConstants)
    {
        IDevice::GetInstance()->DestroyBuffer(m_MeshConstants);
    }
}
