#pragma once

#include <functional>

#include "IDevice.h"

#include <TabiContainers.h>

namespace tabi
{
	class OpenGLDevice : public IDevice
	{
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;

		virtual Texture* CreateTexture(const TextureDescription& a_TextureDescription) override;
		virtual Buffer* CreateBuffer(const BufferDescription& a_BufferDescription) override;
		virtual Shader* CreateShader(const ShaderDescription& a_ShaderDescription) override;
		virtual Sampler* CreateSampler(const SamplerDescription& a_SamplerDescription) override;

		virtual IGraphicsPipeline* CreateGraphicsPipeline(const GraphicePipelineDescription& a_PipelineDescription) override;
		virtual IComputePipeline* CreateComputePipeline(const ComputePipelineDescription& a_ComputePipelineDescription) override;

		virtual IRenderTarget* CreateRenderTarget(const RenderTargetDescription& a_RenderTargetDescription) override;

		virtual ICommandList* CreateCommandList() override;

		virtual void ExecuteCommandList(ICommandList* a_CommandList) override;

		virtual void DestroyTexture(Texture* a_Texture) override;
		virtual void DestroyBuffer(Buffer* a_Buffer) override;
		virtual void DestroyShader(Shader* a_Shader) override;
		virtual void DestroySampler(Sampler* a_Sampler) override;

		virtual void DestroyGraphicsPipeline(IGraphicsPipeline* a_GraphicsPipeline) override;
		virtual void DestroyComputePipeline(IComputePipeline* a_ComputePipeline) override;

		virtual void DestroyRenderTarget(IRenderTarget* a_RenderTarget) override;

		virtual void DestroyCommandList(ICommandList* a_CommandList) override;

		virtual IFence* CreateFence() override;
		virtual void InsertFence(class IFence* a_Fence, uint64_t a_Value) override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;

		virtual void Present() override;

	private:
		tabi::vector<std::function<void()>> m_CommandQueue{ 1024 };
		tabi::queue<class OpenGLFence*> m_PendingFences;
	};
}
