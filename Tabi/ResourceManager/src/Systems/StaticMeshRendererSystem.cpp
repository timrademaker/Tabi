#include "Systems/StaticMeshRendererSystem.h"

#include "Components/StaticMeshComponent.h"

#include <Components/Transform.h>
#include <ComponentManager.h>

#include <IRenderer.h>

void tabi::StaticMeshRenderSystem::OnUpdate(float a_DeltaTime)
{
    TABI_UNUSED(a_DeltaTime);

    auto& renderer = tabi::graphics::IRenderer::GetInstance();

    for (auto& ent : m_Entities)
    {
        auto& mesh = m_ComponentManager->GetComponent<tabi::StaticMeshComponent>(ent);

        if (mesh.m_IsEnabled)
        {
            auto& trans = m_ComponentManager->GetComponent<tabi::Transform>(ent);

            tabi::mat4 transform = tabi::mat4::CreateTransformationMatrix(
                tabi::mat4::Translate(tabi::mat4::Identity(), trans.m_Position),
                tabi::mat4::Scale(tabi::mat4::Identity(), trans.m_Scale),
                tabi::mat4::SetRotation(tabi::mat4::Identity(), mesh.m_RelativeMeshRotation - trans.m_EulerRotation)
            );

            renderer.RenderMesh(*mesh.m_Mesh, transform);
        }
    }
}
