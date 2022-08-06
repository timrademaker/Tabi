#include "OpenGL/OpenGLCommandList.h"

#include "OpenGL/GLConverters.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLComputePipeline.h"
#include "OpenGL/OpenGLGraphicsPipeline.h"
#include "OpenGL/OpenGLRenderTarget.h"
#include "OpenGL/OpenGLSampler.h"
#include "OpenGL/OpenGLTexture.h"

#include "Helpers/FormatInfo.h"
#include "TextureUpdateDescription.h"

#include <glad/glad.h>

#define ENSURE_COMMAND_LIST_IS_RECORDING() TABI_ASSERT(m_IsRecording, "Command list function called while recording is not active!")

void tabi::OpenGLCommandList::BeginRecording()
{
	TABI_ASSERT(m_IsRecording == false, "Command list is already recording!");
	m_IsRecording = true;
}

void tabi::OpenGLCommandList::EndRecording()
{
	TABI_ASSERT(m_IsRecording == true, "Command list is not currently recording!");
	m_IsRecording = false;
}

void tabi::OpenGLCommandList::Reset()
{
	m_PendingCommands.Reset();
	m_IsRecording = false;
}

void tabi::OpenGLCommandList::BindVertexBuffers(int32_t a_FirstSlot, const Buffer* const* a_VertexBuffers, size_t a_NumBuffers)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	// Copy the buffers to a vector so we don't have to rely on a_VertexBuffers remaining valid until the command list is executed
	tabi::vector<const Buffer*> buffers(a_NumBuffers);
	std::copy_n(a_VertexBuffers, a_NumBuffers, buffers.data());

	m_PendingCommands.Add([a_FirstSlot, a_NumBuffers, buffers = std::move(buffers)]
		{
			tabi::vector<GLuint> vertexBuffers(a_NumBuffers);
			tabi::vector<GLsizei> strides(a_NumBuffers);

			for (size_t i = 0; i < a_NumBuffers; ++i)
			{
				const OpenGLBuffer* oglBuffer = static_cast<const OpenGLBuffer*>(buffers[i]);
				TABI_ASSERT(oglBuffer->GetBufferDescription().m_Role == EBufferRole::Vertex);

				vertexBuffers[i] = oglBuffer->GetID();
				strides[i] = buffers[i]->GetBufferDescription().m_Stride;
			}

			const tabi::vector<GLintptr> offsets(a_NumBuffers);

			glBindVertexBuffers(a_FirstSlot, a_NumBuffers, vertexBuffers.data(), offsets.data(), strides.data());
		}
	);
}

void tabi::OpenGLCommandList::BindIndexBuffer(const Buffer* a_IndexBuffer)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_IndexBuffer != nullptr);
	TABI_ASSERT(a_IndexBuffer->GetBufferDescription().m_Role == EBufferRole::Index);

	m_IndexBuffer = a_IndexBuffer;

	m_PendingCommands.Add([buf = static_cast<const OpenGLBuffer*>(a_IndexBuffer)]
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf->GetID());
		}
	);

}

void tabi::OpenGLCommandList::BindConstantBuffer(const Buffer* a_Buffer, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Buffer != nullptr);
	TABI_ASSERT(a_Buffer->GetBufferDescription().m_Role == EBufferRole::Constant);

	m_PendingCommands.Add([buf = static_cast<const OpenGLBuffer*>(a_Buffer), a_Slot]
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, a_Slot, buf->GetID());
		}
	);
}

void tabi::OpenGLCommandList::BindReadWriteBuffer(const Buffer* a_Buffer, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Buffer != nullptr);

	m_PendingCommands.Add([buf = static_cast<const OpenGLBuffer*>(a_Buffer), a_Slot]
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, a_Slot, buf->GetID());
		}
	);
}

void tabi::OpenGLCommandList::BindTexture(const Texture* a_Texture, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Texture != nullptr);

	m_PendingCommands.Add([tex = static_cast<const OpenGLTexture*>(a_Texture), a_Slot]
		{
			glActiveTexture(GL_TEXTURE0 + a_Slot);
			glBindTexture(GLTextureDimension(tex->GetTextureDescription().m_Dimension), tex->GetID());
		}
	);
}

void tabi::OpenGLCommandList::BindWritableTexture(const Texture* a_Texture, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Texture != nullptr);

	m_PendingCommands.Add([tex = static_cast<const OpenGLTexture*>(a_Texture), a_Slot]
		{
			bool textureIsLayered = GL_FALSE;

			switch (tex->GetTextureDescription().m_Dimension)
			{
			case ETextureDimension::Tex1D:
			case ETextureDimension::Tex2D:
			case ETextureDimension::Tex3D:
			case ETextureDimension::CubeMap:
			{
				textureIsLayered = GL_FALSE;
				break;
			}
			case ETextureDimension::Tex1DArray:
			case ETextureDimension::Tex2DArray:
			case ETextureDimension::CubeMapArray:
			{
				textureIsLayered = GL_TRUE;
				break;
			}
			}

			glBindImageTexture(a_Slot, tex->GetID(), 0, textureIsLayered, 0, GL_READ_WRITE, GLFormat(tex->GetTextureDescription().m_Format));
		}
	);
}

void tabi::OpenGLCommandList::BindSampler(const Sampler* a_Sampler, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Sampler != nullptr);

	m_PendingCommands.Add([samp = static_cast<const OpenGLSampler*>(a_Sampler), a_Slot]
		{
			glBindSampler(a_Slot, samp->GetID());
		}
	);
}

void tabi::OpenGLCommandList::InsertBarrier(const Texture* a_Texture)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_UNUSED(a_Texture);

	m_PendingCommands.Add([]
		{
			glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		}
	);
}

void tabi::OpenGLCommandList::InsertBarrier(const Buffer* a_Buffer)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_UNUSED(a_Buffer);

	m_PendingCommands.Add([]
		{
			glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);
		}
	);
}

void tabi::OpenGLCommandList::SetRenderTarget(const RenderTarget* a_RenderTarget)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	if(a_RenderTarget == m_CurrentRenderTarget)
	{
		return;
	}

	m_CurrentRenderTarget = static_cast<const OpenGLRenderTarget*>(a_RenderTarget);

	m_PendingCommands.Add([renderTarget = m_CurrentRenderTarget]
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, renderTarget ? renderTarget->GetID() : 0);
		}
	);
}

void tabi::OpenGLCommandList::ClearRenderTarget(RenderTarget* a_RenderTarget, const float a_ClearColor[4])
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	auto* originalRenderTarget = m_CurrentRenderTarget;
	SetRenderTarget(a_RenderTarget);

	tabi::array<float, 4> clearColor;
	std::copy_n(a_ClearColor, 4, clearColor.begin());

	m_PendingCommands.Add([clearColor = std::move(clearColor)]
		{
			glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	);

	// Rebind the target that was originally bound to prevent unexpectedly rendering to a different render target
	SetRenderTarget(originalRenderTarget);
}

void tabi::OpenGLCommandList::ClearDepthStencil(RenderTarget* a_RenderTarget, float a_DepthValue,
	uint8_t a_StencilValue)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	auto* originalRenderTarget = m_CurrentRenderTarget;
	SetRenderTarget(a_RenderTarget);

	m_PendingCommands.Add([a_DepthValue, a_StencilValue]
		{
			glClearDepthf(a_DepthValue);
			glClearStencil(a_StencilValue);
			glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
	);

	// Rebind the target that was originally bound to prevent unexpectedly rendering to a different render target
	SetRenderTarget(originalRenderTarget);
}

namespace tabi
{
	void CopyDataToTexture1D(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription, const tabi::vector<char>& a_Data)
	{
		glTextureSubImage1D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
			a_UpdateDescription.m_OffsetX,
			a_UpdateDescription.m_DataWidth,
			GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
			a_Data.data()
		);
	}

	void CopyDataToTexture2D(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription, uint32_t a_DataHeight, uint32_t a_OffsetY, const tabi::vector<char>& a_Data)
	{
		glTextureSubImage2D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
			a_UpdateDescription.m_OffsetX, a_OffsetY,
			a_UpdateDescription.m_DataWidth, a_DataHeight,
			GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
			a_Data.data()
		);
	}

	void CopyDataToTexture3D(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription, const tabi::vector<char>& a_Data)
	{
		glTextureSubImage3D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
			a_UpdateDescription.m_OffsetX, a_UpdateDescription.m_OffsetY, a_UpdateDescription.m_OffsetZ,
			a_UpdateDescription.m_DataWidth, a_UpdateDescription.m_DataHeight, a_UpdateDescription.m_DataDepth,
			GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
			a_Data.data()
		);
	}

	void CopyDataToTextureCubemap(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription, const tabi::vector<char>& a_Data)
	{
		const auto faceIndex = static_cast<uint8_t>(a_UpdateDescription.m_CubeFace);
		if(a_Texture->GetTextureDescription().m_Dimension == ETextureDimension::CubeMap)
		{
			glTextureSubImage3D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
				a_UpdateDescription.m_OffsetX, a_UpdateDescription.m_OffsetY, faceIndex,
				a_UpdateDescription.m_DataWidth, a_UpdateDescription.m_DataHeight, 1,
				GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
				a_Data.data()
			);
		}
		else if (a_Texture->GetTextureDescription().m_Dimension == ETextureDimension::CubeMapArray)
		{
			glTextureSubImage3D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
				a_UpdateDescription.m_OffsetX, a_UpdateDescription.m_OffsetY, a_UpdateDescription.m_OffsetZ * 6 + faceIndex,
				a_UpdateDescription.m_DataWidth, a_UpdateDescription.m_DataHeight, 1,
				GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
				a_Data.data()
			);
		}
	}
}

void tabi::OpenGLCommandList::UseGraphicsPipeline(const GraphicsPipeline* a_GraphicsPipeline)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_GraphicsPipeline != nullptr);

	if (a_GraphicsPipeline == m_GraphicsPipeline)
	{
		return;
	}
	
	m_GraphicsPipeline = static_cast<const OpenGLGraphicsPipeline*>(a_GraphicsPipeline);

	m_PendingCommands.Add([pipeline = m_GraphicsPipeline]
		{
			glBindProgramPipeline(pipeline->GetID());
			glBindVertexArray(pipeline->GetVAO());

			const auto & pipelineDesc = pipeline->GetPipelineDescription();

			if (pipelineDesc.m_BlendState.m_BlendEnabled)
			{
				const auto& blend = pipelineDesc.m_BlendState;

				glEnable(GL_BLEND);

				// TODO: glBlend*i() instead when supporting multiple blend targets

				if (blend.m_BlendOperationRGB == blend.m_BlendOperationAlpha)
				{
					glBlendEquation(GLBlendEquation(blend.m_BlendOperationRGB));
				}
				else
				{
					glBlendEquationSeparate(GLBlendEquation(blend.m_BlendOperationRGB), GLBlendEquation(blend.m_BlendOperationAlpha));
				}

				if (blend.m_SourceBlendFactorRGB == blend.m_SourceBlendFactorAlpha && blend.m_DestBlendFactorRGB == blend.m_DestBlendFactorAlpha)
				{
					glBlendFunc(GLBlendFactor(blend.m_SourceBlendFactorRGB), GLBlendFactor(blend.m_DestBlendFactorRGB));
				}
				else
				{
					glBlendFuncSeparate(GLBlendFactor(blend.m_SourceBlendFactorRGB), GLBlendFactor(blend.m_DestBlendFactorRGB), GLBlendFactor(blend.m_SourceBlendFactorAlpha), GLBlendFactor(blend.m_DestBlendFactorAlpha));
				}
			}
			else
			{
				glDisable(GL_BLEND);
			}

			if (pipelineDesc.m_DepthStencilState.m_EnableDepthTest)
			{
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GLComparisonFunction(pipelineDesc.m_DepthStencilState.m_ComparisonFunction));
			}
			else
			{
				glDisable(GL_DEPTH_TEST);
			}

			if(pipelineDesc.m_DepthStencilState.m_FrontStencilState.m_StencilFunc != EComparisonFunction::Never || pipelineDesc.m_DepthStencilState.m_BackStencilState.m_StencilFunc != EComparisonFunction::Never )
			{
				glEnable(GL_STENCIL_TEST);

				const auto& back = pipelineDesc.m_DepthStencilState.m_BackStencilState;
				const auto& front = pipelineDesc.m_DepthStencilState.m_FrontStencilState;

				if (front.m_StencilFunc == back.m_StencilFunc
					&& front.m_ReferenceValue == back.m_ReferenceValue
					&& front.m_StencilMask == back.m_StencilMask)
				{
					glStencilFunc(GLComparisonFunction(front.m_StencilFunc), front.m_ReferenceValue, front.m_StencilMask);
				}
				else
				{
					glStencilFuncSeparate(GL_FRONT, GLComparisonFunction(front.m_StencilFunc), front.m_ReferenceValue, front.m_StencilMask);
					glStencilFuncSeparate(GL_BACK, GLComparisonFunction(back.m_StencilFunc), back.m_ReferenceValue, back.m_StencilMask);
				}

				if (front.m_StencilFailOp == back.m_StencilFailOp
					&& front.m_DepthFailOp == back.m_DepthFailOp
					&& front.m_StencilOp == back.m_StencilOp)
				{
					glStencilOp(GLStencilOperation(front.m_StencilFailOp), GLStencilOperation(front.m_DepthFailOp), GLStencilOperation(front.m_StencilOp));
				}
				else
				{
					glStencilOpSeparate(GL_FRONT, GLStencilOperation(front.m_StencilFailOp), GLStencilOperation(front.m_DepthFailOp), GLStencilOperation(front.m_StencilOp));
					glStencilOpSeparate(GL_BACK, GLStencilOperation(back.m_StencilFailOp), GLStencilOperation(back.m_DepthFailOp), GLStencilOperation(back.m_StencilOp));
				}
			}
			else
			{
				glDisable(GL_STENCIL_TEST);
			}

			if (pipelineDesc.m_RasterizerState.m_CullMode == ECullMode::None)
			{
				glDisable(GL_CULL_FACE);
			}
			else
			{
				glEnable(GL_CULL_FACE);

				glFrontFace(pipelineDesc.m_RasterizerState.m_TriangleFrontIsCounterClockwise ? GL_CCW : GL_CW);
				glCullFace(GLCullMode(pipelineDesc.m_RasterizerState.m_CullMode));
				glPolygonMode(GL_FRONT_AND_BACK, GLPolygonMode(pipelineDesc.m_RasterizerState.m_PolygonMode));
			}
		}
	);
}

void tabi::OpenGLCommandList::UseComputePipeline(const ComputePipeline* a_ComputePipeline)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_ComputePipeline != nullptr);

	if(a_ComputePipeline == m_ComputePipeline)
	{
		return;
	}

	m_ComputePipeline = static_cast<const OpenGLComputePipeline*>(a_ComputePipeline);

	m_PendingCommands.Add([pipeline = m_GraphicsPipeline]
		{
			glBindProgramPipeline(pipeline->GetID());
		}
	);
}

void tabi::OpenGLCommandList::CopyDataToTexture(Texture* a_Texture, const TextureUpdateDescription& a_TextureUpdateDescription)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	// Copy texture data to a staging buffer
	const size_t width = std::max<size_t>(a_TextureUpdateDescription.m_DataWidth, 1);
	const size_t height = std::max<size_t>(a_TextureUpdateDescription.m_DataHeight, 1);
	const size_t depth = std::max<size_t>(a_TextureUpdateDescription.m_DataDepth, 1);
	const size_t bitsPerTexel = GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_FormatSizeInBytes;
	const size_t dataSizeDivisor = pow(2, a_TextureUpdateDescription.m_MipLevel);	// Each mip level takes up half the memory of the previous mip level

	// TODO: Is this correct?
	const size_t texDataBytes = (width * height * depth * bitsPerTexel) / dataSizeDivisor;
	tabi::vector<char> stagedTextureData(texDataBytes);
	std::copy_n(a_TextureUpdateDescription.m_Data, texDataBytes, stagedTextureData.begin());

	m_PendingCommands.Add([tex = static_cast<const OpenGLTexture*>(a_Texture), a_TextureUpdateDescription, data = std::move(stagedTextureData)]
		{
			auto offsetY = a_TextureUpdateDescription.m_OffsetY;
			auto dataHeight = a_TextureUpdateDescription.m_DataHeight;

			switch(tex->GetTextureDescription().m_Dimension)
			{
			case ETextureDimension::Tex1D:
				CopyDataToTexture1D(tex, a_TextureUpdateDescription, data);
				break;
			case ETextureDimension::Tex1DArray:
				offsetY = a_TextureUpdateDescription.m_OffsetZ;
				dataHeight = a_TextureUpdateDescription.m_DataDepth;
			case ETextureDimension::Tex2D:
				CopyDataToTexture2D(tex, a_TextureUpdateDescription, dataHeight, offsetY, data);
				break;
			case ETextureDimension::Tex2DArray:
			case ETextureDimension::Tex3D:
				CopyDataToTexture3D(tex, a_TextureUpdateDescription, data);
				break;
			case ETextureDimension::CubeMap:
			case ETextureDimension::CubeMapArray:
				CopyDataToTextureCubemap(tex, a_TextureUpdateDescription, data);
				break;
			default: 
				TABI_ASSERT(false, "Attempting to copy data to a texture with unexpected dimensions");
				break;
			}
		}
	);
}

void tabi::OpenGLCommandList::CopyDataToBuffer(Buffer* a_Buffer, const char* a_Data, size_t a_DataSize, size_t a_Offset)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Buffer != nullptr);

	TABI_ASSERT(a_Buffer->GetBufferDescription().m_SizeInBytes >= (a_DataSize + a_Offset), "Trying to copy more data into a buffer than would fit");

	tabi::vector<char> stagedBufferData(a_DataSize);
	std::copy_n(a_Data, a_DataSize, stagedBufferData.begin());

	m_PendingCommands.Add([buf = static_cast<const OpenGLBuffer*>(a_Buffer), data = std::move(stagedBufferData), a_DataSize, a_Offset]
		{
			glNamedBufferSubData(buf->GetID(), a_Offset, a_DataSize, data.data());
		}
	);
}

void tabi::OpenGLCommandList::DrawVertices(uint32_t a_VertexCount, uint32_t a_StartVertexLocation)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(m_GraphicsPipeline != nullptr);

	m_PendingCommands.Add([a_VertexCount, a_StartVertexLocation, topology = GLTopology(m_GraphicsPipeline->GetPipelineDescription().m_Topology)]
		{
			glDrawArrays(topology, a_StartVertexLocation, a_VertexCount);
		}
	);
}

void tabi::OpenGLCommandList::DrawInstanced(uint32_t a_VertexCountPerInstance, uint32_t a_InstanceCount,
	uint32_t a_StartVertexLocation)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(m_GraphicsPipeline != nullptr);

	m_PendingCommands.Add([a_VertexCountPerInstance, a_StartVertexLocation, a_InstanceCount, topology = GLTopology(m_GraphicsPipeline->GetPipelineDescription().m_Topology)]
		{
			glDrawArraysInstanced(topology, a_StartVertexLocation, a_VertexCountPerInstance, a_InstanceCount);
		}
	);
}

void tabi::OpenGLCommandList::DrawIndexed(uint32_t a_IndexCount, uint32_t a_StartIndexLocation,
                                          uint32_t a_StartVertexLocation)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(m_GraphicsPipeline != nullptr);

	const auto indexBufferStride = m_IndexBuffer->GetBufferDescription().m_Stride;
	const GLenum indexType = GLType(GetFormatInfo(m_IndexBuffer->GetBufferDescription().m_Format).m_DataType);
	TABI_ASSERT(indexType == GL_UNSIGNED_SHORT || indexType == GL_UNSIGNED_INT || indexType == GL_UNSIGNED_BYTE, "Unsupported index buffer data type");

	const auto startIndexPosition = a_StartIndexLocation * indexBufferStride;
	const auto topology = GLTopology(m_GraphicsPipeline->GetPipelineDescription().m_Topology);

	m_PendingCommands.Add([a_IndexCount, a_StartVertexLocation, topology, startIndexPosition, indexType]
		{
			glDrawElementsBaseVertex(topology, a_IndexCount, indexType, reinterpret_cast<void*>(startIndexPosition), a_StartVertexLocation);
		}
	);
}

void tabi::OpenGLCommandList::DrawIndexedInstanced(uint32_t a_IndexCountPerInstance, uint32_t a_InstanceCount,
	uint32_t a_StartIndexLocation, uint32_t a_StartVertexLocation)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(m_GraphicsPipeline != nullptr);

	const auto indexBufferStride = m_IndexBuffer->GetBufferDescription().m_Stride;
	const GLenum indexType = GLType(GetFormatInfo(m_IndexBuffer->GetBufferDescription().m_Format).m_DataType);
	TABI_ASSERT(indexType == GL_UNSIGNED_SHORT || indexType == GL_UNSIGNED_INT || indexType == GL_UNSIGNED_BYTE, "Unsupported index buffer data type");

	const auto startIndexPosition = a_StartIndexLocation * indexBufferStride;
	const auto topology = GLTopology(m_GraphicsPipeline->GetPipelineDescription().m_Topology);

	m_PendingCommands.Add([a_IndexCountPerInstance, a_InstanceCount, a_StartVertexLocation, topology, indexType, startIndexPosition]
		{
			glDrawElementsInstancedBaseVertex(topology, a_IndexCountPerInstance, indexType, reinterpret_cast<void*>(startIndexPosition), a_InstanceCount, a_StartVertexLocation);
		}
	);
}

void tabi::OpenGLCommandList::DispatchComputePipeline(uint32_t a_GroupCountX, uint32_t a_GroupCountY,
                                                      uint32_t a_GroupCountZ)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(m_ComputePipeline != nullptr);

	m_PendingCommands.Add([a_GroupCountX, a_GroupCountY, a_GroupCountZ]
		{
			glDispatchCompute(a_GroupCountX, a_GroupCountY, a_GroupCountZ);
		}
	);
}

#undef ENSURE_COMMAND_LIST_IS_RECORDING
