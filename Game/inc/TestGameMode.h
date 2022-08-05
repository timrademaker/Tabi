#pragma once

#include  <GameBase.h>

#include "MovableCamera.h"

namespace tabi
{
    class ICommandList;
    class Buffer;
    class GraphicsPipeline;
}

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
    tabi::vector<tabi::Buffer*> m_VertexBuffers;
    tabi::vector<tabi::Buffer*> m_IndexBuffers;

	tabi::Buffer* m_ConstBuffer = nullptr;
    
    tabi::GraphicsPipeline* m_MeshPipeline = nullptr;
    tabi::ICommandList* m_CommandList = nullptr;

    tabi::shared_ptr<MovableCamera> m_Camera;
};