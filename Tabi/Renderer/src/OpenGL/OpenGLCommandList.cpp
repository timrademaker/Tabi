#include "OpenGL/OpenGLCommandList.h"

#include "OpenGL/GLConverters.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLGraphicsPipeline.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLSampler.h"

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
	m_PendingCommands.clear();
	m_IsRecording = false;
}

void tabi::OpenGLCommandList::BindVertexBuffers(int32_t a_FirstSlot, Buffer** a_VertexBuffers, size_t a_NumBuffers)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	// Copy the buffers to a vector so we don't have to rely on a_VertexBuffers remaining valid until the command list is executed
	tabi::vector<Buffer*> buffers{ a_NumBuffers };
	for (size_t i = 0; i < a_NumBuffers; ++i)
	{
		buffers.push_back(a_VertexBuffers[i]);
	}

	m_PendingCommands.push_back([a_FirstSlot, a_NumBuffers, buffers = std::move(buffers)]
		{
			tabi::vector<GLuint> vertexBuffers{8};
			tabi::vector<GLsizei> strides{8};

			for (size_t i = 0; i < a_NumBuffers; ++i)
			{
				const OpenGLBuffer* oglBuffer = static_cast<OpenGLBuffer*>(buffers[i]);

				vertexBuffers.push_back(oglBuffer->GetID());
				strides.push_back(buffers[i]->GetBufferDescription().m_Stride);
			}

			glBindVertexBuffers(a_FirstSlot, a_NumBuffers, vertexBuffers.data(), nullptr, strides.data());
		}
	);
}

void tabi::OpenGLCommandList::BindIndexBuffer(Buffer* a_IndexBuffer)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_IndexBuffer != nullptr);

	m_IndexBuffer = a_IndexBuffer;

	m_PendingCommands.push_back([buf = static_cast<OpenGLBuffer*>(a_IndexBuffer)]
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf->GetID());
		}
	);

}

void tabi::OpenGLCommandList::BindConstantBuffer(Buffer* a_Buffer, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Buffer != nullptr);

	m_PendingCommands.push_back([buf = static_cast<OpenGLBuffer*>(a_Buffer), a_Slot]
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, a_Slot, buf->GetID());
		}
	);
}

void tabi::OpenGLCommandList::BindReadWriteBuffer(Buffer* a_Buffer, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Buffer != nullptr);

	m_PendingCommands.push_back([buf = static_cast<OpenGLBuffer*>(a_Buffer), a_Slot]
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, a_Slot, buf->GetID());
		}
	);
}

void tabi::OpenGLCommandList::BindTexture(Texture* a_Texture, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Texture != nullptr);

	m_PendingCommands.push_back([tex = static_cast<OpenGLTexture*>(a_Texture), a_Slot]
		{
			glActiveTexture(GL_TEXTURE0 + a_Slot);
			glBindTexture(GLTextureDimension(tex->GetTextureDescription().m_Dimension), tex->GetID());
		}
	);
}

void tabi::OpenGLCommandList::BindWritableTexture(Texture* a_Texture, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Texture != nullptr);

	m_PendingCommands.push_back([tex = static_cast<OpenGLTexture*>(a_Texture), a_Slot]
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

void tabi::OpenGLCommandList::BindSampler(Sampler* a_Sampler, int32_t a_Slot)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_Sampler != nullptr);

	m_PendingCommands.push_back([samp = static_cast<OpenGLSampler*>(a_Sampler), a_Slot]
		{
			glBindSampler(a_Slot, samp->GetID());
		}
	);
}

void tabi::OpenGLCommandList::InsertBarrier(Texture* a_Texture)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_UNUSED(a_Texture);

	m_PendingCommands.push_back([]
		{
			glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		}
	);
}

void tabi::OpenGLCommandList::InsertBarrier(Buffer* a_Buffer)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_UNUSED(a_Buffer);

	m_PendingCommands.push_back([]
		{
			glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);
		}
	);
}

namespace tabi
{
	void CopyDataToTexture1D(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription)
	{
		glTextureSubImage1D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
			a_UpdateDescription.m_OffsetX,
			a_UpdateDescription.m_DataWidth,
			GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
			a_UpdateDescription.m_Data
		);
	}

	void CopyDataToTexture2D(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription, uint32_t a_DataHeight, uint32_t a_OffsetY)
	{
		glTextureSubImage2D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
			a_UpdateDescription.m_OffsetX, a_OffsetY,
			a_UpdateDescription.m_DataWidth, a_DataHeight,
			GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
			a_UpdateDescription.m_Data
		);
	}

	void CopyDataToTexture3D(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription)
	{
		glTextureSubImage3D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
			a_UpdateDescription.m_OffsetX, a_UpdateDescription.m_OffsetY, a_UpdateDescription.m_OffsetZ,
			a_UpdateDescription.m_DataWidth, a_UpdateDescription.m_DataHeight, a_UpdateDescription.m_DataDepth,
			GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
			a_UpdateDescription.m_Data
		);
	}

	void CopyDataToTextureCubemap(const tabi::OpenGLTexture* a_Texture, const tabi::TextureUpdateDescription& a_UpdateDescription)
	{
		const auto faceIndex = static_cast<uint8_t>(a_UpdateDescription.m_CubeFace);
		if(a_Texture->GetTextureDescription().m_Dimension == ETextureDimension::CubeMap)
		{
			glTextureSubImage3D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
				a_UpdateDescription.m_OffsetX, a_UpdateDescription.m_OffsetY, faceIndex,
				a_UpdateDescription.m_DataWidth, a_UpdateDescription.m_DataHeight, 1,
				GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
				a_UpdateDescription.m_Data
			);
		}
		else if (a_Texture->GetTextureDescription().m_Dimension == ETextureDimension::CubeMapArray)
		{
			glTextureSubImage3D(a_Texture->GetID(), a_UpdateDescription.m_MipLevel,
				a_UpdateDescription.m_OffsetX, a_UpdateDescription.m_OffsetY, a_UpdateDescription.m_OffsetZ * 6 + faceIndex,
				a_UpdateDescription.m_DataWidth, a_UpdateDescription.m_DataHeight, 1,
				GLFormat(a_Texture->GetTextureDescription().m_Format), GLType(GetFormatInfo(a_Texture->GetTextureDescription().m_Format).m_DataType),
				a_UpdateDescription.m_Data
			);
		}
	}
}

void tabi::OpenGLCommandList::UseGraphicsPipeline(GraphicsPipeline* a_GraphicsPipeline)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(a_GraphicsPipeline != nullptr);
	
	m_GraphicsPipeline = static_cast<OpenGLGraphicsPipeline*>(a_GraphicsPipeline);

	m_PendingCommands.emplace_back([pipeline = m_GraphicsPipeline]
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
				const auto& back = pipelineDesc.m_DepthStencilState.m_BackStencilState;
				const auto& front = pipelineDesc.m_DepthStencilState.m_FrontStencilState;

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GLComparisonFunction(pipelineDesc.m_DepthStencilState.m_ComparisonFunction));

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
				glDisable(GL_DEPTH_TEST);
			}

			if (pipelineDesc.m_RasterizerState.m_CullMode == ECullMode::None)
			{
				glDisable(GL_CULL_FACE);
			}
			else
			{
				glEnable(GL_CULL_FACE);

				glCullFace(GLCullMode(pipelineDesc.m_RasterizerState.m_CullMode));
				glPolygonMode(GL_FRONT_AND_BACK, GLPolygonMode(pipelineDesc.m_RasterizerState.m_PolygonMode));
			}
		}
	);
}

void tabi::OpenGLCommandList::CopyDataToTexture(Texture* a_Texture, const TextureUpdateDescription& a_TextureUpdateDescription)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();

	m_PendingCommands.push_back([tex = static_cast<OpenGLTexture*>(a_Texture), updateDescription = a_TextureUpdateDescription]
		{
			auto offsetY = updateDescription.m_OffsetY;
			auto dataHeight = updateDescription.m_DataHeight;

			switch(tex->GetTextureDescription().m_Dimension)
			{
			case ETextureDimension::Tex1D:
				CopyDataToTexture1D(tex, updateDescription);
				break;
			case ETextureDimension::Tex1DArray:
				offsetY = updateDescription.m_OffsetZ;
				dataHeight = updateDescription.m_DataDepth;
			case ETextureDimension::Tex2D:
				CopyDataToTexture2D(tex, updateDescription, dataHeight, offsetY);
				break;
			case ETextureDimension::Tex2DArray:
			case ETextureDimension::Tex3D:
				CopyDataToTexture3D(tex, updateDescription);
				break;
			case ETextureDimension::CubeMap:
			case ETextureDimension::CubeMapArray:
				CopyDataToTextureCubemap(tex, updateDescription);
				break;
			default: 
				TABI_ASSERT(false, "Attempting to copy data to a texture with unexpected dimensions");
				break;
			}
		}
	);
}

void tabi::OpenGLCommandList::DrawVertices(uint32_t a_VertexCount, uint32_t a_StartVertexLocation)
{
	ENSURE_COMMAND_LIST_IS_RECORDING();
	TABI_ASSERT(m_GraphicsPipeline != nullptr);

	m_PendingCommands.emplace_back([a_VertexCount, a_StartVertexLocation, topology = GLTopology(m_GraphicsPipeline->GetPipelineDescription().m_Topology)]
		{
			glDrawArrays(topology, a_StartVertexLocation, a_VertexCount);
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

	m_PendingCommands.emplace_back([a_IndexCount, a_StartVertexLocation, topology, startIndexPosition, indexType]
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

	m_PendingCommands.emplace_back([a_IndexCountPerInstance, a_InstanceCount, a_StartVertexLocation, topology, indexType, startIndexPosition]
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

	m_PendingCommands.emplace_back([a_GroupCountX, a_GroupCountY, a_GroupCountZ]
		{
			glDispatchCompute(a_GroupCountX, a_GroupCountY, a_GroupCountZ);
		}
	);
}

#undef ENSURE_COMMAND_LIST_IS_RECORDING
