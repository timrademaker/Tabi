#pragma once

namespace tabi
{
	struct ComputePipelineDescription
	{
		class IShader* m_ComputeShader = nullptr;
	};

	class ComputePipeline
	{
	public:
		inline const ComputePipelineDescription& GetPipelineDescription() const
		{
			return m_PipelineDescription;
		}

	protected:
		ComputesPipeline(const ComputePipelineDescription& a_PipelineDescription)
			: m_PipelineDescription(a_PipelineDescription)
		{}

	private:
		ComputePipelineDescription m_PipelineDescription;
	};
}
