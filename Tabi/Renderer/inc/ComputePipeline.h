#pragma once

#include "Shader.h"

#include <TabiMacros.h>

namespace tabi
{
	struct ComputePipelineDescription
	{
		const class Shader* m_ComputeShader = nullptr;
	};

	class ComputePipeline
	{
	public:
		TABI_NO_COPY(ComputePipeline);
		TABI_NO_MOVE(ComputePipeline);

		inline const ComputePipelineDescription& GetPipelineDescription() const
		{
			return m_PipelineDescription;
		}

	protected:
		ComputePipeline(const ComputePipelineDescription& a_PipelineDescription)
			: m_PipelineDescription(a_PipelineDescription)
		{
			TABI_ASSERT(a_PipelineDescription.m_ComputeShader && a_PipelineDescription.m_ComputeShader->GetShaderType() == EShaderType::Compute);
		}
		~ComputePipeline() = default;

	private:
		ComputePipelineDescription m_PipelineDescription;
	};
}
