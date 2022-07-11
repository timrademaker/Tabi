#pragma once

namespace tabi
{
	class ICommandList
	{
	public:
		// TODO: Constructor/destructor

		virtual void BeginRecording() = 0;
		virtual void EndRecording() = 0;

		// virtual void BindBuffer(class IBuffer*, int32_t a_Slot) = 0;	// What kind of buffer? Storage?
		virtual void BindVertexBuffers(int32_t a_FirstSlot, class IBuffer** a_VertexBuffers, size_t a_NumBuffers) = 0;
		virtual void BindIndexBuffer(class IBuffer* a_IndexBuffer) = 0;
		// virtual void BindConstantBuffer(class IBuffer*, int32_t a_Slot) = 0;

		virtual void BindTexture(class ITexture*, int32_t a_Slot) = 0;
		virtual void BindWritableTexture(class ITexture*, int32_t a_Slot) = 0;	// Texture that can be read from and written to

		virtual void InsertBarrier() = 0; // TODO: Barrier types?

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
		virtual void DrawInstanced(uint32_t a_VertexCountPerInstance, uint32_ a_InstanceCount, uint32_t a_StartVertexLocation = 0) = 0;
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

		virtual void BindGraphicsPipeline(class IGraphicsPipeline*) = 0;
		virtual void BindComputePipeline(class IComputePipeline*) = 0;
	};
}