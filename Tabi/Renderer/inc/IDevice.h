#pragma once

#include <cstdint>

namespace tabi
{
	class IDevice
	{
	public:
		IDevice(IDevice&) = delete;
		IDevice(const IDevice&) = delete;
		IDevice(IDevice&&) = delete;

		static IDevice* GetInstance();

		/**
		 * @brief Initialize the rendering device
		 */
		virtual void Initialize() = 0;
		/**
		 * @brief Finalize the rendering device
		 */
		virtual void Finalize() = 0;

		/**
		 * @brief Create a new texture
		 * @param a_TextureDescription A struct describing the texture to create
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created texture
		 */
		virtual class Texture* CreateTexture(const struct TextureDescription& a_TextureDescription, const char* a_DebugName = nullptr) = 0;
		/**
		 * @brief Create a new buffer
		 * @param a_BufferDescription A struct describing the buffer to create
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created buffer
		 */
		virtual class Buffer* CreateBuffer(const struct BufferDescription& a_BufferDescription, const char* a_DebugName = nullptr) = 0;
		/**
		 * @brief Create a new shader
		 * @param a_ShaderDescription A struct describing the shader to create
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created shader
		 */
		virtual class Shader* CreateShader(const struct ShaderDescription& a_ShaderDescription, const char* a_DebugName = nullptr) = 0;
		/**
		 * @brief Create a new sampler
		 * @param a_SamplerDescription A struct describing the sampler to create
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created sampler
		 */
		virtual class Sampler* CreateSampler(const struct SamplerDescription& a_SamplerDescription, const char* a_DebugName = nullptr) = 0;

		/**
		 * @brief Create a new graphics pipeline object
		 * @param a_PipelineDescription A struct describing the graphics pipeline to create
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created graphics pipeline
		 */
		virtual class GraphicsPipeline* CreateGraphicsPipeline(const struct GraphicsPipelineDescription& a_PipelineDescription, const char* a_DebugName = nullptr) = 0;
		/**
		 * @brief Create a new compute pipeline object
		 * @param a_ComputePipelineDescription A struct describing the compute pipeline to create
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created compute pipeline
		 */
		virtual class ComputePipeline* CreateComputePipeline(const struct ComputePipelineDescription& a_ComputePipelineDescription, const char* a_DebugName = nullptr) = 0;

		/**
		 * @brief Create a new render target
		 * @param a_RenderTargetDescription A struct describing the render target to create
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created render target
		 */
		virtual class IRenderTarget* CreateRenderTarget(const struct RenderTargetDescription& a_RenderTargetDescription, const char* a_DebugName = nullptr) = 0;
		/**
		 * @brief Create a new command list
		 * @param a_DebugName The debug name to assign to the created object (if supported)
		 * @returns The created command list
		 */
		virtual class ICommandList* CreateCommandList(const char* a_DebugName = nullptr) = 0;
		/**
		 * @brief Execute a command list
		 * @param a_CommandList The command list to execute
		 */
		virtual void ExecuteCommandList(class ICommandList* a_CommandList) = 0;

		virtual void DestroyTexture(class Texture* a_Texture) = 0;
		virtual void DestroyBuffer(class Buffer* a_Buffer) = 0;
		virtual void DestroyShader(class Shader* a_Shader) = 0;
		virtual void DestroySampler(class Sampler* a_Sampler) = 0;
		virtual void DestroyGraphicsPipeline(class GraphicsPipeline* a_GraphicsPipeline) = 0;
		virtual void DestroyComputePipeline(class ComputePipeline* a_ComputePipeline) = 0;
		virtual void DestroyRenderTarget(class IRenderTarget* a_RenderTarget) = 0;
		virtual void DestroyCommandList(class ICommandList* a_CommandList) = 0;

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

		/**
		 * @brief Start a new frame
		 */
		virtual void BeginFrame() = 0;
		/**
		 * @brief End the current frame
		 */
		virtual void EndFrame() = 0;
		/**
		 * @brief Present the backbuffer to the screen
		 */
		virtual void Present() = 0;

	protected:
		IDevice() = default;
		virtual ~IDevice() = default;
	};
}
