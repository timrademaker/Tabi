#pragma once

#include "Sampler.h"

namespace tabi
{
	class OpenGLSampler : public Sampler
	{
	public:
		TABI_NO_COPY(OpenGLSampler);
		TABI_NO_MOVE(OpenGLSampler);

		OpenGLSampler(SamplerDescription a_SamplerDescription)
			: Sampler(a_SamplerDescription)
		{}

		void Destroy()
		{
			glDeleteSamplers(1, &m_SamplerID);
			m_SamplerID = 0;
		}

		inline GLuint GetID() const { return m_SamplerID; }
		inline void SetID(const GLuint a_SamplerID)
		{
			TABI_ASSERT(m_SamplerID == 0, "Sampler ID already set!");
			m_SamplerID = a_SamplerID;
		}

	private:
		GLuint m_SamplerID = 0;
	};
}
