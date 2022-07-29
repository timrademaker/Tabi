#pragma once

#include "ComputePipeline.h"

namespace tabi
{
	class OpenGLComputePipeline : public ComputePipeline
	{
	public:
		TABI_NO_COPY(OpenGLComputePipeline);
		TABI_NO_MOVE(OpenGLComputePipeline);

		OpenGLComputePipeline(const ComputePipelineDescription& a_PipelineDescription)
			: ComputePipeline(a_PipelineDescription)
		{}
		~OpenGLComputePipeline() = default;

		void Destroy()
		{
			glDeleteProgramPipelines(1, &m_PipelineID);
			m_PipelineID = 0;
		}

		inline GLuint GetID() const { return m_PipelineID; }
		inline void SetID(GLuint a_PipelineID)
		{
			TABI_ASSERT(m_PipelineID == 0, "Pipeline ID already set!");
			m_PipelineID = a_PipelineID;
		}

	private:
		GLuint m_PipelineID = 0;
	};
}
