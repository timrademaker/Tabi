#pragma once

#include  <GameBase.h>

#include <Math/vec4.h>
#include <Math/mat4.h>

#include "MovableCamera.h"

namespace tabi
{
    class ICommandList;
    class Buffer;
    class GraphicsPipeline;

    class Texture;
    class RenderTarget;
}

struct Model
{
    tabi::Buffer* m_VertexBuffer;
    tabi::Buffer* m_IndexBuffer;
    tabi::Texture* m_ColorTexture = nullptr;

    size_t m_VertexCount = 0;
    size_t m_IndexCount = 0;

    tabi::vec3 m_Position{};
    tabi::vec3 m_Rotation{};
    tabi::vec3 m_Scale{ 1, 1, 1 };

    tabi::vec4 m_BaseColorFactor{ 1.0f, 1.0f, 1.0f, 1.0f };
};

struct ModelData
{
    tabi::mat4 m_ModelMatrix;
    tabi::vec4 m_BaseColorFactor{ 1.0f, 1.0f, 1.0f, 1.0f };
};

class TestGameMode : public tabi::GameBase
{
public:
    TestGameMode(const char* a_Name, const int a_Width, const int a_Height, const bool a_Vsync)
    : GameBase(a_Name, a_Width, a_Height, a_Vsync)
    {};
    virtual ~TestGameMode() override = default;

    virtual bool OnInitialize() override;
    virtual void OnUpdate(float a_DeltaTime) override;
    virtual void OnRender() override;
    virtual void OnDestroy() override;

private:
    tabi::vector<Model> m_Models;
    tabi::Buffer* m_ConstBuffer = nullptr;
    tabi::Buffer* m_ModelData = nullptr;
    
    tabi::GraphicsPipeline* m_MeshPipeline = nullptr;
    tabi::ICommandList* m_CommandList = nullptr;

    tabi::shared_ptr<MovableCamera> m_Camera;

    tabi::GraphicsPipeline* m_UIPipeline = nullptr;
    Model m_UIQuad;
    tabi::Texture* m_DrawTex = nullptr;
    tabi::Texture* m_DepthTex = nullptr;
    tabi::RenderTarget* m_RenderTarget = nullptr;
};
