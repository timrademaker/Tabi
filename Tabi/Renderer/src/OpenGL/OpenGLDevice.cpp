#include "OpenGL/OpenGLDevice.h"

#include "OpenGL/GLConverters.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLCommandList.h"
#include "OpenGL/OpenGLFence.h"
#include "OpenGL/OpenGLRenderTarget.h"
#include "OpenGL/OpenGLSampler.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLGraphicsPipeline.h"
#include "OpenGL/OpenGLComputePipeline.h"

#include "Helpers/RendererLogger.h"
#include "Helpers/FormatInfo.h"

namespace tabi
{
	void CreateTexture1D(GLuint a_Texture, GLsizei a_MipLevels, EFormat a_Format, GLsizei a_Width)
	{
		glTextureStorage1D(a_Texture, a_MipLevels, GLInternalFormat(a_Format), a_Width);
	}

	void CreateTexture2D(GLuint a_Texture, GLsizei a_MipLevels, EFormat a_Format, GLsizei a_Width, GLsizei a_Height)
	{
		glTextureStorage2D(a_Texture, a_MipLevels, GLInternalFormat(a_Format), a_Width, a_Height);
	}

	void CreateTexture3D(GLuint a_Texture, GLsizei a_MipLevels, EFormat a_Format, GLsizei a_Width, GLsizei a_Height, GLsizei a_Depth)
	{
		glTextureStorage3D(a_Texture, a_MipLevels, GLInternalFormat(a_Format), a_Width, a_Height, a_Depth);
	}

	void SetObjectDebugLabel(GLenum a_Target, GLuint a_Id, const char* a_DebugName)
	{
#if defined(DEBUG_GRAPHICS)
		glObjectLabel(a_Target, a_Id, -1, a_DebugName);
#endif
	}
}

tabi::Texture* tabi::OpenGLDevice::CreateTexture(const TextureDescription& a_TextureDescription, const char* a_DebugName)
{
	TABI_ASSERT(a_TextureDescription.m_Dimension != ETextureDimension::Unknown);

	auto* tex = new OpenGLTexture(a_TextureDescription);
	m_CommandQueue.emplace_back([tex, a_DebugName]
		{
			GLuint id;
			glCreateTextures(GLTarget(tex->GetTextureDescription().m_Dimension), 1, &id);
			TABI_ASSERT(id != 0, "Failed to create texture");
			tex->SetID(id);
			SetObjectDebugLabel(GL_TEXTURE, id, a_DebugName);
			
			const auto& texDescription = tex->GetTextureDescription();

			switch (texDescription.m_Dimension)
			{
			case ETextureDimension::Tex1D:
			{
				CreateTexture1D(id, texDescription.m_MipLevels, texDescription.m_Format, texDescription.m_Width);
				break;
			}
			case ETextureDimension::Tex1DArray:
			{
				CreateTexture2D(id, texDescription.m_MipLevels, texDescription.m_Format, texDescription.m_Width, texDescription.m_Depth);
				break;
			}
			case ETextureDimension::Tex2D:
			{
				CreateTexture2D(id, texDescription.m_MipLevels, texDescription.m_Format, texDescription.m_Width, texDescription.m_Height);
				break;
			}
			case ETextureDimension::Tex2DArray:
			case ETextureDimension::Tex3D:
			{
				CreateTexture3D(id, texDescription.m_MipLevels, texDescription.m_Format, texDescription.m_Width, texDescription.m_Height, texDescription.m_Depth);
				break;
			}
			case ETextureDimension::CubeMap:
			{
				TABI_ASSERT(texDescription.m_Width == texDescription.m_Height, "Width and height should be equal for cubemaps");
				CreateTexture2D(id, texDescription.m_MipLevels, texDescription.m_Format, texDescription.m_Width, texDescription.m_Height);
				break;
			}
			case ETextureDimension::CubeMapArray:
			{
				TABI_ASSERT(texDescription.m_Width == texDescription.m_Height, "Width and height should be equal for cubemaps");
				CreateTexture3D(id, texDescription.m_MipLevels, texDescription.m_Format, texDescription.m_Width, texDescription.m_Height, texDescription.m_Depth);
				break;
			}
			}

			if (texDescription.m_MipLevels > 0)
			{
				glTextureParameteri(id, GL_TEXTURE_MAX_LEVEL, texDescription.m_MipLevels);
			}
		}
	);

	return tex;
}

tabi::Buffer* tabi::OpenGLDevice::CreateBuffer(const BufferDescription& a_BufferDescription, const char* a_DebugName)
{
	if (a_BufferDescription.m_Role == EBufferRole::Index)
	{
		const auto dataType = GetFormatInfo(a_BufferDescription.m_Format).m_DataType;
		TABI_ASSERT(dataType == EDataType::Ubyte || dataType == EDataType::Ushort || dataType == EDataType::Uint, "Unsupported index buffer data type");
	}

	auto* buf = new OpenGLBuffer(a_BufferDescription);
	m_CommandQueue.emplace_back([buf, a_DebugName]
		{
			GLuint id;
			glCreateBuffers(1, &id);
			TABI_ASSERT(id != 0, "Failed to create buffer");
			buf->SetID(id);
			SetObjectDebugLabel(GL_BUFFER, id, a_DebugName);

			const auto& bufDescription = buf->GetBufferDescription();

			GLenum usage = GL_STATIC_DRAW;
			switch (bufDescription.m_Role)
			{
			case EBufferRole::Vertex:
			case EBufferRole::Index:
			{
				usage = GL_STATIC_DRAW;
				break;
			}
			case EBufferRole::Constant:
			{
				usage = GL_DYNAMIC_DRAW;
				break;
			}
			}

			// Create a buffer with no data to at least allocate memory for the buffer
			glNamedBufferData(id, bufDescription.m_SizeInBytes, nullptr, usage);

			// TODO: Check if glBufferStorage with flag GL_DYNAMIC_STORAGE_BIT would be a better fit here.
			// Maybe pass data to the buffer creation already in order to not always require that flag.
		}
	);

	return buf;
}

tabi::Shader* tabi::OpenGLDevice::CreateShader(const ShaderDescription& a_ShaderDescription, const char* a_DebugName)
{
	auto* shader = new OpenGLShader(a_ShaderDescription.m_ShaderType);

	m_CommandQueue.emplace_back([shader, data = a_ShaderDescription.m_Data, dataLen = a_ShaderDescription.m_DataLength, a_DebugName]
		{
			const GLuint shaderId = glCreateShader(GLShaderType(shader->GetShaderType()));
			TABI_ASSERT(shaderId != 0, "Failed to create shader");

			
			if(dataLen > 0)
			{
				const GLint dataLength = dataLen;
				glShaderSource(shaderId, 1, &data, &dataLength);
			}
			else
			{
				glShaderSource(shaderId, 1, &data, nullptr);
			}
			
			glCompileShader(shaderId);

			GLint isCompiled = 0;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE)
			{
				GLint shaderLogLength = 0;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &shaderLogLength);

				std::vector<GLchar> shaderLog(shaderLogLength);
				glGetShaderInfoLog(shaderId, shaderLogLength, &shaderLogLength, &shaderLog[0]);
				glDeleteShader(shaderId);

				LOG_ERROR("Failed to compile shader. Error: %s", shaderLog.data());
				TABI_ASSERT(isCompiled == GL_TRUE, "Shader failed to compile!");
				return;
			}

			const GLuint programId = glCreateProgram();
			TABI_ASSERT(shaderId != 0, "Failed to create shader program");

			glProgramParameteri(programId, GL_PROGRAM_SEPARABLE, GL_TRUE);
			glAttachShader(programId, shaderId);
			glLinkProgram(programId);

			GLint isLinked = 0;
			glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);

			if(isLinked == GL_FALSE)
			{
				GLint programLogLength = 0;
				glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &programLogLength);

				std::vector<GLchar> programLog(programLogLength);
				glGetProgramInfoLog(programId, programLogLength, &programLogLength, programLog.data());
				glDeleteProgram(programId);
				glDeleteShader(shaderId);

				LOG_ERROR("Failed to link shader program. Error: %s", programLog.data());
				TABI_ASSERT(isLinked == GL_TRUE, "Shader program failed to link!");

				glDeleteProgram(programId);
				return;
			}

			glDetachShader(programId, shaderId);

			SetObjectDebugLabel(GL_PROGRAM, programId, a_DebugName);
			shader->SetID(programId);
		}
	);

	return shader;
}

tabi::Sampler* tabi::OpenGLDevice::CreateSampler(const SamplerDescription& a_SamplerDescription, const char* a_DebugName)
{
	auto* sampler = new OpenGLSampler(a_SamplerDescription);

	m_CommandQueue.emplace_back([sampler, a_DebugName]
		{
			GLuint id = 0;
			glCreateSamplers(1, &id);
			TABI_ASSERT(id != 0, "Failed to create sampler");
			sampler->SetID(id);
			SetObjectDebugLabel(GL_SAMPLER, id, a_DebugName);

			const auto& samplerDescription = sampler->GetSamplerDescription();

			{
				const GLenum wrapMode = GLWrapMode(samplerDescription.m_WrapMode);
				glSamplerParameteri(id, GL_TEXTURE_WRAP_S, wrapMode);
				glSamplerParameteri(id, GL_TEXTURE_WRAP_T, wrapMode);
				glSamplerParameteri(id, GL_TEXTURE_WRAP_R, wrapMode);

				if (samplerDescription.m_WrapMode == EWrapMode::Border)
				{
					glSamplerParameterfv(id, GL_TEXTURE_BORDER_COLOR, samplerDescription.m_BorderColor);
				}
			}

			glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, GLMinFilter(samplerDescription.m_MinFilter, samplerDescription.m_MipMapMode));
			glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, GLMagFilter(samplerDescription.m_MagFilter));

			glSamplerParameterf(id, GL_TEXTURE_MIN_LOD, samplerDescription.m_MinLOD);
			glSamplerParameterf(id, GL_TEXTURE_MAX_LOD, samplerDescription.m_MaxLOD);
			glSamplerParameterf(id, GL_TEXTURE_LOD_BIAS, samplerDescription.m_MipLODBias);

			glSamplerParameteri(id, GL_TEXTURE_COMPARE_FUNC, GLComparisonFunction(samplerDescription.m_ComparisonFunc));
		}
	);

	return sampler;
}

tabi::GraphicsPipeline* tabi::OpenGLDevice::CreateGraphicsPipeline(
	const GraphicsPipelineDescription& a_PipelineDescription, const char* a_DebugName)
{
	auto* pipeline = new OpenGLGraphicsPipeline(a_PipelineDescription);

	m_CommandQueue.emplace_back([pipeline, a_DebugName]
		{
			GLuint pipelineId = 0;
			glCreateProgramPipelines(1, &pipelineId);
			pipeline->SetID(pipelineId);
			TABI_ASSERT(pipelineId != 0, "Failed to create program pipeline");

			SetObjectDebugLabel(GL_PROGRAM_PIPELINE, pipelineId, a_DebugName);

			const auto& pipelineDesc = pipeline->GetPipelineDescription();

			if (pipelineDesc.m_VertexShader)
			{
				glUseProgramStages(pipelineId, GL_VERTEX_SHADER_BIT, static_cast<const OpenGLShader*>(pipelineDesc.m_VertexShader)->GetID());
			}
			if (pipelineDesc.m_PixelShader)
			{
				glUseProgramStages(pipelineId, GL_FRAGMENT_SHADER_BIT, static_cast<const OpenGLShader*>(pipelineDesc.m_PixelShader)->GetID());
			}

			glValidateProgramPipeline(pipelineId);

			GLuint vaoId = 0;
			glCreateVertexArrays(1, &vaoId);
			TABI_ASSERT(vaoId != 0, "Failed to create VAO");
			pipeline->SetVAO(vaoId);

			GLuint dataOffset = 0;
			for (GLuint i = 0; i < pipelineDesc.m_VertexInputLayout.m_NumInputElements; ++i)
			{
				const auto& inputElement = pipelineDesc.m_VertexInputLayout.m_InputElements[i];
				const auto& formatInfo = GetFormatInfo(inputElement.m_Format);

				glVertexArrayAttribFormat(vaoId, i, formatInfo.m_ComponentCount, GLType(formatInfo.m_DataType), formatInfo.m_IsNormalized ? GL_TRUE : GL_FALSE, dataOffset);
				glEnableVertexArrayAttrib(vaoId, i);
				glVertexArrayAttribBinding(vaoId, i, inputElement.m_InputSlot);

				glVertexArrayBindingDivisor(vaoId, i, inputElement.m_InstanceDataStepRate);

				dataOffset += formatInfo.m_FormatSizeInBits;
			}
		}
	);

	return pipeline;
}

tabi::ComputePipeline* tabi::OpenGLDevice::CreateComputePipeline(const ComputePipelineDescription& a_ComputePipelineDescription, const char* a_DebugName)
{
	auto* pipeline = new OpenGLComputePipeline(a_ComputePipelineDescription);

	m_CommandQueue.emplace_back([pipeline, a_DebugName]
		{
			GLuint pipelineId = 0;
			glCreateProgramPipelines(1, &pipelineId);
			pipeline->SetID(pipelineId);
			TABI_ASSERT(pipelineId != 0, "Failed to create program pipeline");

			SetObjectDebugLabel(GL_PROGRAM_PIPELINE, pipelineId, a_DebugName);

			const auto& pipelineDesc = pipeline->GetPipelineDescription();

			if (pipelineDesc.m_ComputeShader)
			{
				glUseProgramStages(pipelineId, GL_VERTEX_SHADER_BIT, static_cast<const OpenGLShader*>(pipelineDesc.m_ComputeShader)->GetID());
			}

			glValidateProgramPipeline(pipelineId);
		}
	);

	return pipeline;
}

tabi::RenderTarget* tabi::OpenGLDevice::CreateRenderTarget(const RenderTargetDescription& a_RenderTargetDescription,
	const char* a_DebugName)
{
	{
		const auto* tex = a_RenderTargetDescription.m_RenderTexture;
		const auto* depth = a_RenderTargetDescription.m_DepthStencilBuffer;
		TABI_ASSERT(tex && tex->GetTextureDescription().m_Role == ETextureRole::RenderTexture);
		TABI_ASSERT(depth && depth->GetTextureDescription().m_Role == ETextureRole::DepthStencil);
	}

	auto* renderTarget = new OpenGLRenderTarget(a_RenderTargetDescription);

	m_CommandQueue.emplace_back([renderTarget, a_DebugName]
		{
			GLuint id = 0;
			glCreateFramebuffers(1, &id);
			renderTarget->SetID(id);
			TABI_ASSERT(id != 0, "Failed to create render target");

			const auto& desc = renderTarget->GetRenderTargetDescription();
			const auto* colorBuffer = static_cast<OpenGLTexture*>(desc.m_RenderTexture);
			const auto* depthStencil = static_cast<OpenGLTexture*>(desc.m_DepthStencilBuffer);
			glNamedFramebufferTexture(id, GL_COLOR_ATTACHMENT0, colorBuffer->GetID(), desc.m_MipLevel);
			glNamedFramebufferTexture(id, GL_DEPTH_STENCIL_ATTACHMENT, depthStencil->GetID(), desc.m_MipLevel);

			// TODO: m_TextureLayer is ignored as glFramebufferTexture3D() is not used. Does this matter?

			SetObjectDebugLabel(GL_FRAMEBUFFER, id, a_DebugName);
		}
	);

	return renderTarget;
}

tabi::ICommandList* tabi::OpenGLDevice::CreateCommandList(const char* a_DebugName)
{
	TABI_UNUSED(a_DebugName);
	return new OpenGLCommandList;
}

#define DESTROY_RESOURCE(T, resource) m_ResourceDeletionQueue.emplace_back([ptr = static_cast<T*>(resource)] { \
	ptr->Destroy(); \
	delete ptr;\
})

void tabi::OpenGLDevice::DestroyTexture(Texture* a_Texture)
{
	TABI_ASSERT(a_Texture != nullptr);
	DESTROY_RESOURCE(OpenGLTexture, a_Texture);
}

void tabi::OpenGLDevice::DestroyBuffer(Buffer* a_Buffer)
{
	TABI_ASSERT(a_Buffer != nullptr);
	DESTROY_RESOURCE(OpenGLBuffer, a_Buffer);
}

void tabi::OpenGLDevice::DestroyShader(Shader* a_Shader)
{
	TABI_ASSERT(a_Shader != nullptr);
	DESTROY_RESOURCE(OpenGLShader, a_Shader);
}

void tabi::OpenGLDevice::DestroySampler(Sampler* a_Sampler)
{
	TABI_ASSERT(a_Sampler != nullptr);
	DESTROY_RESOURCE(OpenGLSampler, a_Sampler);
}

void tabi::OpenGLDevice::DestroyGraphicsPipeline(GraphicsPipeline* a_GraphicsPipeline)
{
	TABI_ASSERT(a_GraphicsPipeline != nullptr);
	DESTROY_RESOURCE(OpenGLGraphicsPipeline, a_GraphicsPipeline);
}

void tabi::OpenGLDevice::DestroyComputePipeline(ComputePipeline* a_ComputePipeline)
{
	TABI_ASSERT(a_ComputePipeline != nullptr);
	DESTROY_RESOURCE(OpenGLComputePipeline, a_ComputePipeline);
}

void tabi::OpenGLDevice::DestroyRenderTarget(RenderTarget* a_RenderTarget)
{
	TABI_ASSERT(a_RenderTarget != nullptr);
	DESTROY_RESOURCE(OpenGLRenderTarget, a_RenderTarget);
}

void tabi::OpenGLDevice::DestroyCommandList(ICommandList* a_CommandList)
{
	TABI_ASSERT(a_CommandList != nullptr);
	delete static_cast<OpenGLCommandList*>(a_CommandList);
}

void tabi::OpenGLDevice::DestroyFence(IFence* a_Fence)
{
	TABI_ASSERT(a_Fence != nullptr);
	DESTROY_RESOURCE(OpenGLFence, a_Fence);
}
#undef DESTROY_RESOURCE

tabi::IFence* tabi::OpenGLDevice::CreateFence()
{
	return new OpenGLFence;
}

void tabi::OpenGLDevice::InsertFence(IFence* a_Fence, uint64_t a_Value)
{
	m_CommandQueue.emplace_back([a_Value, fence = static_cast<OpenGLFence*>(a_Fence)]
		{
			fence->SetCompletionValue(a_Value);
			fence->m_FenceSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
			TABI_ASSERT(fence->m_FenceSync != nullptr, "Failed to create fence");
		}
	);
}

void tabi::OpenGLDevice::EndFrame()
{
	m_CommandQueue.emplace_back([pendingFences = &m_PendingFences]
		{
			while (!pendingFences->empty())
			{
				auto* fence = pendingFences->front();
				const auto result = glClientWaitSync(fence->m_FenceSync, 0, 0);
				if (result == GL_ALREADY_SIGNALED || result == GL_CONDITION_SATISFIED)
				{
					fence->Complete();
					pendingFences->pop();
				}
				else
				{
					// Other fences won't have been completed either, as they were inserted later
					break;
				}
			}
		}
	);

	for (auto& func : m_CommandQueue)
	{
		func();
	}
	m_CommandQueue.clear();

	for(auto& func : m_ResourceDeletionQueue)
	{
		func();
	}
	m_ResourceDeletionQueue.clear();
}
