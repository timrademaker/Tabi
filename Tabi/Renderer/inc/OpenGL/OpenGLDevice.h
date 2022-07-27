#pragma once

#include "IDevice.h"

#include <TabiContainers.h>

#include <functional>

namespace tabi
{
	class OpenGLDevice : public IDevice
	{
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;

		virtual Texture* CreateTexture(const TextureDescription& a_TextureDescription, const char* a_DebugName = nullptr) override;
		virtual Buffer* CreateBuffer(const BufferDescription& a_BufferDescription, const char* a_DebugName = nullptr) override;
		virtual Shader* CreateShader(const ShaderDescription& a_ShaderDescription, const char* a_DebugName = nullptr) override;
		virtual Sampler* CreateSampler(const SamplerDescription& a_SamplerDescription, const char* a_DebugName = nullptr) override;

		virtual GraphicsPipeline* CreateGraphicsPipeline(const GraphicePipelineDescription& a_PipelineDescription, const char* a_DebugName = nullptr) override;
		virtual ComputePipeline* CreateComputePipeline(const ComputePipelineDescription& a_ComputePipelineDescription, const char* a_DebugName = nullptr) override;

		virtual IRenderTarget* CreateRenderTarget(const RenderTargetDescription& a_RenderTargetDescription, const char* a_DebugName = nullptr) override;

		virtual ICommandList* CreateCommandList(const char* a_DebugName = nullptr) override;

		virtual void ExecuteCommandList(ICommandList* a_CommandList) override;

		virtual void DestroyTexture(Texture* a_Texture) override;
		virtual void DestroyBuffer(Buffer* a_Buffer) override;
		virtual void DestroyShader(Shader* a_Shader) override;
		virtual void DestroySampler(Sampler* a_Sampler) override;

		virtual void DestroyGraphicsPipeline(GraphicsPipeline* a_GraphicsPipeline) override;
		virtual void DestroyComputePipeline(ComputePipeline* a_ComputePipeline) override;

		virtual void DestroyRenderTarget(IRenderTarget* a_RenderTarget) override;

		virtual void DestroyCommandList(ICommandList* a_CommandList) override;

		virtual IFence* CreateFence() override;
		virtual void InsertFence(class IFence* a_Fence, uint64_t a_Value) override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;

		virtual void Present() override;

	private:
		tabi::vector<std::function<void()>> m_CommandQueue{ 1024 };

		tabi::vector<std::function<void()>> m_ResourceDeletionQueue{ 64 };

		tabi::queue<class OpenGLFence*> m_PendingFences;
	};
}
