#pragma once

#include "Shader.h"

namespace tabi
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(EShaderType a_ShaderType)
			: Shader(a_ShaderType)
		{}
		~OpenGLShader()
		{
			glDeleteShader(m_ShaderID);
		}

		inline GLuint GetID() const { return m_ShaderID; }
		inline void SetID(const GLuint a_ShaderID)
		{
			TABI_ASSERT(m_ShaderID == 0, "Buffer ID already set!");
			m_ShaderID = a_ShaderID;
		}

	private:
		GLuint m_ShaderID = 0;
	};
}
