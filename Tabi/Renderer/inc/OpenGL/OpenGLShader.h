#pragma once

#include "Shader.h"

namespace tabi
{
	class OpenGLShader : public Shader
	{
	public:
		TABI_NO_COPY(OpenGLShader);
		TABI_NO_MOVE(OpenGLShader);

		OpenGLShader(EShaderType a_ShaderType)
			: Shader(a_ShaderType)
		{}

		void Destroy()
		{
			glDeleteProgram(m_ProgramID);
			m_ProgramID = 0;
		}

		inline GLuint GetID() const { return m_ProgramID; }
		inline void SetID(const GLuint a_ProgramID)
		{
			TABI_ASSERT(m_ProgramID == 0, "Program ID already set!");
			m_ProgramID = a_ProgramID;
		}

	private:
		GLuint m_ProgramID = 0;
	};
}
