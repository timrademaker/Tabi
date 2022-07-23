#pragma once

#include "ICommandList.h"

#include <TabiContainers.h>

#include <functional>

namespace tabi
{
	class OpenGLCommandList : public ICommandList
	{
	protected:
		TABI_NO_COPY(OpenGLCommandList);
		TABI_NO_MOVE(OpenGLCommandList);

		~OpenGLCommandList() = default;

	public:
		virtual void BeginRecording() override;
		virtual void EndRecording() override;
		virtual void Reset() override;

		virtual void BindVertexBuffers(int32_t a_FirstSlot, Buffer** a_VertexBuffers, size_t a_NumBuffers) override;
		virtual void BindIndexBuffer(Buffer* a_IndexBuffer) override;
		virtual void BindConstantBuffer(Buffer* a_Buffer, int32_t a_Slot) override;
		virtual void BindReadWriteBuffer(Buffer* a_Buffer, int32_t a_Slot) override;

		virtual void BindTexture(Texture* a_Texture, int32_t a_Slot) override;
		virtual void BindWritableTexture(Texture* a_Texture, int32_t a_Slot) override;

		virtual void InsertBarrier() override;

		virtual void SetRenderTarget(IRenderTarget* a_RenderTarget) override;
		virtual void ClearRenderTarget(class IRenderTarget* a_RenderTarget, float a_ClearColor[4]) override;
		virtual void ClearDepthStencil(IRenderTarget* a_RenderTarget, float a_DepthValue, uint8_t a_StencilValue) override;

		virtual void UseGraphicsPipeline(IGraphicsPipeline* a_GraphicsPipeline) override;
		virtual void UseComputePipeline(IComputePipeline* a_ComputePipeline) override;
		
		virtual void CopyDataToTexture(Texture* a_Texture, const TextureUpdateDescription& a_TextureUpdateDescription) override;
		virtual void CopyDataToBuffer(Buffer* a_Buffer, const char* a_Data, size_t a_DataSize, size_t a_Offset) override;

		virtual void DrawVertices(uint32_t a_VertexCount, uint32_t a_StartVertexLocation) override;
		virtual void DrawIndexed(uint32_t a_IndexCount, uint32_t a_StartIndexLocation, uint32_t a_StartVertexLocation) override;
		virtual void DrawIndexedInstanced(uint32_t a_IndexCountPerInstance, uint32_t a_InstanceCount,
			uint32_t a_StartIndexLocation, uint32_t a_StartVertexLocation) override;

		virtual void DispatchComputePipeline(uint32_t a_GroupCountX, uint32_t a_GroupCountY, uint32_t a_GroupCountZ) override;

	private:
		bool m_IsRecording = false;

		// TODO: This is private now, but OpenGLDevice will need to access this in order to execute a command list
		tabi::vector<std::function<void()>> m_PendingCommands{128};
	};
}