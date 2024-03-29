#pragma once

#include "Buffer.h"

#include <TabiMacros.h>

#include <glad/gl.h>

namespace tabi
{
	class OpenGLBuffer : public Buffer
	{
	public:
		TABI_NO_COPY(OpenGLBuffer);
		TABI_NO_MOVE(OpenGLBuffer);

		OpenGLBuffer(BufferDescription a_BufferDescription)
			: Buffer(a_BufferDescription)
		{}

		void Destroy()
		{
			glDeleteBuffers(1, &m_BufferID);
			m_BufferID = 0;
		}

		inline GLuint GetID() const { return m_BufferID; }
		inline void SetID(const GLuint a_BufferID)
		{
			TABI_ASSERT(m_BufferID == 0, "Buffer ID already set!");
			m_BufferID = a_BufferID;
		}

	private:
		GLuint m_BufferID = 0;
	};
}
