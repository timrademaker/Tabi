#pragma once

#include "RenderTarget.h"

namespace tabi
{
	class OpenGLRenderTarget : public RenderTarget
	{
	public:
		TABI_NO_COPY(OpenGLRenderTarget);
		TABI_NO_MOVE(OpenGLRenderTarget);

		OpenGLRenderTarget(RenderTargetDescription a_RenderTargetDescription)
			: RenderTarget(a_RenderTargetDescription)
		{}
		~OpenGLRenderTarget() = default;

		void Destroy()
		{
			glDeleteFramebuffers(1, &m_FrameBufferID);
			m_FrameBufferID = 0;
		}

		inline GLuint GetID() const { return m_FrameBufferID; }
		inline void SetID(const GLuint a_FrameBufferID)
		{
			TABI_ASSERT(m_FrameBufferID == 0, "Framebuffer ID already set!");
			m_FrameBufferID = a_FrameBufferID;
		}

	private:
		GLuint m_FrameBufferID = 0;
	};
}
