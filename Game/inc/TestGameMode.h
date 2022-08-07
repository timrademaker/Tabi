#pragma once

#include  <GameBase.h>

#include "MovableCamera.h"

namespace tabi
{
    class ICommandList;
    class Buffer;
    class GraphicsPipeline;
}

struct Model
{
    tabi::Buffer* m_VertexBuffer;
    tabi::Buffer* m_IndexBuffer;

    size_t m_VertexCount = 0;
    size_t m_IndexCount = 0;

    tabi::vec3 m_Position{};
    tabi::vec3 m_Rotation{};
    tabi::vec3 m_Scale{ 1, 1, 1 };
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
};
