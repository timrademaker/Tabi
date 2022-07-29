#pragma once

#include <TabiMacros.h>

namespace tabi
{
	struct ComputePipelineDescription
	{
		class Shader* m_ComputeShader = nullptr;
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
		{}
		~ComputePipeline() = default;

	private:
		ComputePipelineDescription m_PipelineDescription;
	};
}
