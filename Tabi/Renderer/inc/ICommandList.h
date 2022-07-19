#pragma once

namespace tabi
{
	class ICommandList
	{
	public:
		/**
		 * @brief Start recording commands
		 */
		virtual void BeginRecording() = 0;
		/**
		* @brief Stop recording commands
		*/
		virtual void EndRecording() = 0;

		/**
		 * @brief Bind vertex buffers to be used
		 * @param a_FirstSlot The index of the first slot to bind the vertex buffers to
		 * @param a_VertexBuffers The buffers to bind
		 * @param a_NumBuffers The number of buffers to bind
		 */
		virtual void BindVertexBuffers(int32_t a_FirstSlot, class Buffer** a_VertexBuffers, size_t a_NumBuffers) = 0;
		/**
		 * @brief Bind an index buffer to be used
		 * @param a_IndexBuffer The buffer to bind
		 */
		virtual void BindIndexBuffer(class Buffer* a_IndexBuffer) = 0;
		/**
		 * @brief Bind a buffer that can be read from by shaders
		 * @param a_Buffer The buffer to bind
		 * @param a_Slot The slot to bind the buffer to
		 */
		virtual void BindConstantBuffer(class Buffer* a_Buffer, int32_t a_Slot) = 0;
		/**
		 * @brief Bind a buffer that shaders can read from and write to
		 * @param a_Buffer The buffer to bind
		 * @param a_Slot The slot to bind the buffer to
		 *
		 * @note: In OpenGL, this would be a SSBO or buffer texture. In D3D, this would be a UAV.
		 */
		virtual void BindReadWriteBuffer(class Buffer* a_Buffer, int32_t a_Slot) = 0;

		/**
		 * @brief Bind a texture to a shader slot
		 * @param a_Texture The texture to bind
		 * @param a_Slot The slot to bind the texture to
		 */
		virtual void BindTexture(class Texture* a_Texture, int32_t a_Slot) = 0;
		/**
		 * @brief Bind a read/write texture to a shader slot
		 * @param a_Texture The texture to bind
		 * @param a_Slot The slot to bind the texture to
		 */
		virtual void BindWritableTexture(class Texture* a_Texture, int32_t a_Slot) = 0;

		/**
		 * @brief Insert a memory barrier into the command stream
		 */
		virtual void InsertBarrier() = 0;

		/**
		 * @brief Attach a render target to render to with subsequent draw calls
		 * @param a_RenderTarget The render target to use. nullptr represents the screen's render target
		 */
		virtual void SetRenderTarget(class IRenderTarget* a_RenderTarget) = 0;
		/**
		 * @brief Clear a render target's color buffer
		 * @param a_RenderTarget The render target to clear. nullptr represents the screen's render target
		 * @param a_ClearColor The RGBA color to fill the render target with
		 */
		virtual void ClearRenderTarget(class IRenderTarget* a_RenderTarget, float a_ClearColor[4]) = 0;
		/**
		 * @brief Clear a render target's depth-stencil buffer
		 * @param a_RenderTarget The render target to clear. nullptr represents the screen's render target
		 * @param a_DepthValue The value to clear the depth buffer with. Should be between 0.0 and 1.0
		 * @param a_StencilValue The value to clear the stencil buffer with
		 */
		virtual void ClearDepthStencil(class IRenderTarget* a_RenderTarget, float a_DepthValue = 0.0f, uint8_t a_StencilValue = 0) = 0;

		/*
		 * @brief Start using a certain graphics pipeline
		 * @param a_GraphicsPipeline The graphics pipeline to use
		 */
		virtual void UseGraphicsPipeline(class IGraphicsPipeline* a_GraphicsPipeline) = 0;
		/*
		 * @brief Start using a certain compute pipeline
		 * @param a_ComputePipeline The compute pipeline to use
		 */
		virtual void UseComputePipeline(class IComputePipeline* a_ComputePipeline) = 0;

		/**
		 * @brief Copy data to a texture
		 * @param a_Texture The texture to copy the data to
		 * @param a_TextureUpdateDescription A struct describing the data to copy to the texture
		 */
		virtual void CopyDataToTexture(class Texture* a_Texture, const struct TextureUpdateDescription& a_TextureUpdateDescription) = 0;

		/**
		 * @brief Copy data to a buffer
		 * @param a_Buffer The buffer to copy the data to
		 * @param a_Data The data to copy to the buffer
		 * @param a_DataSize The amount of data to copy
		 * @param a_Offset The offset in the buffer's memory at which to start replacing the existing data
		 */
		virtual void CopyDataToBuffer(class Buffer* a_Buffer, const char* a_Data, size_t a_DataSize, size_t a_Offset) = 0;

		/**
		 * @brief Draw vertices
		 * @param a_VertexCount The number of vertices to draw
		 * @param a_StartVertexLocation The offset to the first vertex to draw
		 */
		virtual void DrawVertices(uint32_t a_VertexCount, uint32_t a_StartVertexLocation = 0) = 0;
		/**
		 * @brief Draw instanced vertices
		 * @param a_VertexCountPerInstance The number of vertices to draw per instance
		 * @param a_InstanceCount The number of instances to draw
		 * @param a_StartVertexLocation The offset to the first vertex to draw
		 *
		 * @note: While D3D supports specifying a start instance offset, OpenGL does not appear to support this.
		 */
		virtual void DrawInstanced(uint32_t a_VertexCountPerInstance, uint32_t a_InstanceCount, uint32_t a_StartVertexLocation = 0) = 0;
		/**
		 * @brief Draw indexed vertices
		 * @param a_IndexCount The number of indices to draw
		 * @param a_StartIndexLocation The offset to the first index to draw
		 * @param a_StartVertexLocation The offset to the first vertex to draw
		 */
		virtual void DrawIndexed(uint32_t a_IndexCount, uint32_t a_StartIndexLocation = 0, uint32_t a_StartVertexLocation = 0) = 0;
		/**
		 * @brief Draw indexed, instanced vertices
		 * @param a_IndexCountPerInstance The number of indices to draw per instance
		 * @param a_InstanceCount The number of instances to draw
		 * @param a_StartIndexLocation The offset to the first index to draw
		 * @param a_StartVertexLocation The offset to the first vertex to draw
		 *
		 * @note: While D3D supports specifying a start instance offset, OpenGL does not appear to support this.
		 */
		virtual void DrawIndexedInstanced(uint32_t a_IndexCountPerInstance, uint32_t a_InstanceCount, uint32_t a_StartIndexLocation = 0, uint32_t a_StartVertexLocation = 0) = 0;

		/**
		 * @brief Dispatch a compute pipeline
		 * @param a_GroupCountX The number of groups dispatched in the x direction
		 * @param a_GroupCountY The number of groups dispatched in the y direction
		 * @param a_GroupCountZ The number of groups dispatched in the z direction
		 */
		virtual void DispatchComputePipeline(uint32_t a_GroupCountX, uint32_t a_GroupCountY, uint32_t a_GroupCountZ) = 0;
	};
}
