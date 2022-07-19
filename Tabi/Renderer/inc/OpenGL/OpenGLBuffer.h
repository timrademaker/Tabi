#pragma once

#include "Buffer.h"

#include <glad/glad.h>

namespace tabi
{
	class OpenGLBuffer : public Buffer
	{
	public:
		inline GLuint GetBufferID() const { return m_BufferID; }

	private:
		GLuint m_BufferID = 0;
	};
}
