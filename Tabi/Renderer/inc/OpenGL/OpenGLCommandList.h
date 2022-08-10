#pragma once

#include "ICommandList.h"
#include "TextureUpdateDescription.h"
#include "Helpers/ExecutionQueue.h"

#include <TabiContainers.h>


namespace tabi
{
	class OpenGLCommandList : public ICommandList
	{
	protected:
		TABI_NO_COPY(OpenGLCommandList);
		TABI_NO_MOVE(OpenGLCommandList);

	public:
		OpenGLCommandList(const char* a_DebugName = nullptr)
		{
			if(a_DebugName)
			{
				m_DebugName = tabi::string(a_DebugName);
			}
		}
		~OpenGLCommandList() = default;

		virtual void BeginRecording() override;
		virtual void EndRecording() override;
		virtual void Reset() override;

		virtual void BindVertexBuffers(int32_t a_FirstSlot, const Buffer* const* a_VertexBuffers, size_t a_NumBuffers) override;
		virtual void BindIndexBuffer(const Buffer* a_IndexBuffer) override;
		virtual void BindConstantBuffer(const Buffer* a_Buffer, int32_t a_Slot) override;
		virtual void BindReadWriteBuffer(const Buffer* a_Buffer, int32_t a_Slot) override;

		virtual void BindTexture(const Texture* a_Texture, int32_t a_Slot) override;
		virtual void BindWritableTexture(const Texture* a_Texture, int32_t a_Slot) override;

		virtual void BindSampler(const Sampler* a_Sampler, int32_t a_Slot) override;

		virtual void InsertBarrier(const Texture* a_Texture) override;
		virtual void InsertBarrier(const Buffer* a_Buffer) override;

		virtual void SetRenderTarget(const RenderTarget* a_RenderTarget) override;
		virtual void ClearRenderTarget(RenderTarget* a_RenderTarget, const float a_ClearColor[4]) override;
		virtual void ClearDepthStencil(RenderTarget* a_RenderTarget, float a_DepthValue, uint8_t a_StencilValue) override;

		virtual void UseGraphicsPipeline(const GraphicsPipeline* a_GraphicsPipeline) override;
		virtual void UseComputePipeline(const ComputePipeline* a_ComputePipeline) override;
		
		virtual void CopyDataToTexture(Texture* a_Texture, const TextureUpdateDescription& a_TextureUpdateDescription) override;
		virtual void CopyDataToBuffer(Buffer* a_Buffer, const void* a_Data, size_t a_DataSize, size_t a_Offset = 0) override;

		virtual void DrawVertices(uint32_t a_VertexCount, uint32_t a_StartVertexLocation) override;
		virtual void DrawInstanced(uint32_t a_VertexCountPerInstance, uint32_t a_InstanceCount, uint32_t a_StartVertexLocation = 0) override;
		virtual void DrawIndexed(uint32_t a_IndexCount, uint32_t a_StartIndexLocation, uint32_t a_StartVertexLocation) override;
		virtual void DrawIndexedInstanced(uint32_t a_IndexCountPerInstance, uint32_t a_InstanceCount,
			uint32_t a_StartIndexLocation, uint32_t a_StartVertexLocation) override;

		virtual void DispatchComputePipeline(uint32_t a_GroupCountX, uint32_t a_GroupCountY, uint32_t a_GroupCountZ) override;

		virtual void SetViewport(int32_t a_X, int32_t a_Y, int32_t a_Width, int32_t a_Height, float a_MinDepth = 0.0f, float a_MaxDepth = 1.0f) override;

		/**
		 * @brief Get the command list's pending commands
		 */
		inline const tabi::ExecutionQueue& GetPendingCommands() const { return m_PendingCommands; }
	private:
		bool m_IsRecording = false;

		const class OpenGLGraphicsPipeline* m_GraphicsPipeline = nullptr;
		const class OpenGLComputePipeline* m_ComputePipeline = nullptr;

		const Buffer* m_IndexBuffer = nullptr;

		tabi::ExecutionQueue m_PendingCommands{ 128 };

		tabi::string m_DebugName;
	};
}
