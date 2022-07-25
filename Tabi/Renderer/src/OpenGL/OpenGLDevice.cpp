#include "OpenGL/OpenGLDevice.h"

#include "OpenGL/Converters.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLCommandList.h"
#include "OpenGL/OpenGLFence.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"

#include "Helpers/RendererLogger.h"

namespace tabi
{
	Texture* OpenGLDevice::CreateTexture(const TextureDescription& a_TextureDescription, const char* a_DebugName)
	{
		auto* tex = new OpenGLTexture(a_TextureDescription);
		m_CommandQueue.emplace_back([tex, a_DebugName]
			{
				GLuint id;
				glGenTextures(1, &id);
				TABI_ASSERT(id != 0, "Failed to create texture");
				
				const auto& texDescription = tex->GetTextureDescription();
				auto texHeight = texDescription.m_Height;

				const GLenum bindTarget = GLTarget(texDescription.m_Dimension);
				glBindTexture(bindTarget, id);

				switch (texDescription.m_Dimension)
				{
				case ETextureDimension::Tex1D:
				{
					glTexImage1D(bindTarget, 0, GLInternalFormat(texDescription.m_Format),
						texDescription.m_Width,
						0, GLFormat(texDescription.m_Format), GLType(texDescription.m_Format),
						nullptr
					);
					break;
				}
				case ETextureDimension::Tex1DArray:
					texHeight = texDescription.m_Depth;
				case ETextureDimension::Tex2D:
				{
					glTexImage2D(bindTarget, 0, GLInternalFormat(texDescription.m_Format),
						texDescription.m_Width, texHeight,
						0, GLFormat(texDescription.m_Format), GLType(texDescription.m_Format),
						nullptr
					);
					break;
				}
				case ETextureDimension::Tex2DArray:
				case ETextureDimension::Tex3D:
				{
					glTexImage3D(bindTarget, 0, GLInternalFormat(texDescription.m_Format),
						texDescription.m_Width, texDescription.m_Height, texDescription.m_Depth,
						0, GLFormat(texDescription.m_Format), GLType(texDescription.m_Format),
						nullptr
					);
					break;
				}
				case ETextureDimension::CubeMap:
				{
					TABI_ASSERT(texDescription.m_Width == texDescription.m_Height, "Width and height should be equal for cubemaps");
					for (uint8_t i = 0; i < 6; ++i)
					{
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, texDescription.m_Width, texDescription.m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					}
					break;
				}
				case ETextureDimension::CubeMapArray:
				{
					TABI_ASSERT(texDescription.m_Width == texDescription.m_Height, "Width and height should be equal for cubemaps");
					break;
				}
				}

				if (texDescription.m_MipLevels > 0)
				{
					glTexParameteri(bindTarget, GL_TEXTURE_MAX_LEVEL, texDescription.m_MipLevels);
				}

				glBindTexture(bindTarget, 0);

#if defined(DEBUG_GRAPHICS)
				if (a_DebugName)
				{
					glObjectLabel(GL_TEXTURE, id, strlen(a_DebugName), a_DebugName);
				}
#endif

				tex->SetID(id);
			}
		);

		return tex;
	}

	Buffer* OpenGLDevice::CreateBuffer(const BufferDescription& a_BufferDescription, const char* a_DebugName)
	{
		auto* buf = new OpenGLBuffer(a_BufferDescription);
		m_CommandQueue.emplace_back([buf, a_DebugName]
			{
				GLuint id;
				glGenBuffers(1, &id);
				TABI_ASSERT(id != 0, "Failed to create buffer");

				const auto& bufDescription = buf->GetBufferDescription();

				const GLenum bindTarget = GLTarget(bufDescription.m_Role);
				glBindBuffer(bindTarget, id);

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

				glBufferData(bindTarget, bufDescription.m_SizeInBytes, nullptr, usage);
				glBindBuffer(bindTarget, 0);

#if defined(DEBUG_GRAPHICS)
				if (a_DebugName)
				{
					glObjectLabel(GL_BUFFER, id, strlen(a_DebugName), a_DebugName);
				}
#endif

				buf->SetID(id);
			}
		);

		return buf;
	}

	Shader* OpenGLDevice::CreateShader(const ShaderDescription& a_ShaderDescription, const char* a_DebugName)
	{
		auto* shader = new OpenGLShader(a_ShaderDescription.m_ShaderType);

		m_CommandQueue.emplace_back([shader, data = a_ShaderDescription.m_Data, dataLen = a_ShaderDescription.m_DataLength, a_DebugName]
			{
				const GLuint id = glCreateShader(GLShaderType(shader->GetShaderType()));
				TABI_ASSERT(id != 0, "Failed to create shader");

				const GLint dataLength = dataLen;
				glShaderSource(id, 1, &data, &dataLength);
				glCompileShader(id);

				GLint isCompiled = 0;
				glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

				if (isCompiled == GL_FALSE)
				{
					GLint shaderLogLength = 0;
					glGetShaderiv(id, GL_INFO_LOG_LENGTH, &shaderLogLength);

					std::vector<GLchar> shaderLog(shaderLogLength);
					glGetShaderInfoLog(id, shaderLogLength, &shaderLogLength, &shaderLog[0]);
					glDeleteShader(id);

					LOG_ERROR("Failed to compile shader. Error: %s", shaderLog.data());
					TABI_ASSERT(isCompiled == GL_TRUE, "Shader failed to compile!");

					delete shader;
					return nullptr;
				}

				// TODO: Create shader program (and use program pipeline objects for the graphics/compute pipeline classes)?

#if defined(DEBUG_GRAPHICS)
				if (a_DebugName)
				{
					glObjectLabel(GL_SHADER, id, strlen(a_DebugName), a_DebugName);
				}
#endif
				
				shader->SetID(id);
			}
		);

		return shader;
	}

#define DESTROY_RESOURCE(T, resource) m_DeletionQueue.emplace_back([ptr = static_cast<T*>(resource)] { delete ptr; })

	void OpenGLDevice::DestroyTexture(Texture* a_Texture)
	{
		DESTROY_RESOURCE(OpenGLTexture, a_Texture);
	}

	void OpenGLDevice::DestroyBuffer(Buffer* a_Buffer)
	{
		DESTROY_RESOURCE(OpenGLBuffer, a_Buffer);
	}

	void OpenGLDevice::DestroyShader(Shader* a_Shader)
	{
		DESTROY_RESOURCE(OpenGLShader, a_Shader);
	}
#undef DESTROY_RESOURCE

	IFence* OpenGLDevice::CreateFence()
	{
		return new OpenGLFence;
	}

	void OpenGLDevice::InsertFence(class IFence* a_Fence, uint64_t a_Value)
	{
		m_CommandQueue.emplace_back([fence = static_cast<OpenGLFence*>(a_Fence)]
			{
				fence->m_FenceSync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
				TABI_ASSERT(fence->m_FenceSync != nullptr, "Failed to create buffer");
			}
		);
	}

	void OpenGLDevice::EndFrame()
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

		for(auto& func : m_DeletionQueue)
		{
			func();
		}
	}
}
