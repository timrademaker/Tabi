#pragma once

namespace tabi
{
	class IDevice
	{
		IDevice() = default;
		IDevice(IDevice&) = delete;
		IDevice(const IDevice&) = delete;
		IDevice(IDevice&&) = delete;
		virtual IDevice() = default;

	public:
		virtual void Initialize() = 0;
		virtual void Finalize() = 0;

		// NOTE: D3D12 uploads using a command list, but maybe just give the device a separate command list that uploads textures (and is executed at the end of a frame if needed)?
		virtual class ITexture* CreateTexture(const struct TextureDescription&, const char* a_Data, size_t a_DataSize) = 0;
		virtual class IBuffer* CreateBuffer(const struct BufferDescription&) = 0;
		virtual class ISampler* CreateSampler(const struct SamplerDescription&) = 0;

		virtual class IGraphicsPipeline* CreateGraphicsPipeline(const struct GraphicePipelineDescription&) = 0;
		virtual class IComputePipeline* CreateComputePipeline(const struct ComputePipelineDescription&) = 0;

		virtual class IRenderTarget* CreateRenderTarget() = 0;
		virtual class ICommandList* CreateCommandList() = 0;

		virtual void ExecuteCommandList(class ICommandList*) = 0;

		/**
		 * @brief Create a new fence object
		 * @returns A handle to the created fence
		 */
		virtual class IFence* CreateFence() = 0;
		/**
		 * @brief Insert a fence into the command stream
		 * @param a_Fence The fence to insert
		 * @param a_Value The value of the fence after it has been signaled
		 */
		virtual void InsertFence(class IFence* a_Fence, uint64_t a_Value) = 0;


		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
		virtual void Present() = 0;
	};
}