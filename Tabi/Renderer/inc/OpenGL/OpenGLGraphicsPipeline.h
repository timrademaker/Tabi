#pragma once

#include "GraphicsPipeline.h"

namespace tabi
{
	class OpenGLGraphicsPipeline : public GraphicsPipeline
	{
	public:
		TABI_NO_COPY(OpenGLGraphicsPipeline);
		TABI_NO_MOVE(OpenGLGraphicsPipeline);

		OpenGLGraphicsPipeline(const GraphicsPipelineDescription& a_GraphicsPipelineDescription)
			: GraphicsPipeline(a_GraphicsPipelineDescription)
		{}
		~OpenGLGraphicsPipeline() = default;

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

		inline GLuint GetVAO() const { return m_VAO;  }
		inline void SetVAO(GLuint a_VAO)
		{
			TABI_ASSERT(m_VAO == 0, "VAO ID already set!");
			m_VAO = a_VAO;
		}

	private:
		GLuint m_PipelineID = 0;
		GLuint m_VAO = 0;
	};
}
