#pragma once

#include "Shader.h"

#include "Enums/ComparisonFunction.h"
#include "Enums/GraphicsPipelineEnums.h"

#include <TabiContainers.h>
#include <TabiMacros.h>

namespace tabi
{
	struct BlendState
	{
		bool m_BlendEnabled = false;
		EBlendFactor m_SourceBlendFactorRGB = EBlendFactor::One;
		EBlendFactor m_DestBlendFactorRGB = EBlendFactor::Zero;
		EBlendOperation m_BlendOperationRGB = EBlendOperation::Add;

		EBlendFactor m_SourceBlendFactorAlpha = EBlendFactor::One;
		EBlendFactor m_DestBlendFactorAlpha = EBlendFactor::Zero;
		EBlendOperation m_BlendOperationAlpha = EBlendOperation::Add;

		// Describes which colors can be drawn to the blend target
		EColorMask m_ColorWriteMask = EColorMask::All;
	};

	struct RasterizerState
	{
		EPolygonMode m_PolygonMode = EPolygonMode::Fill;
		ECullMode m_CullMode = ECullMode::Back;
		bool m_ScissorEnabled = false;

		// If true, a triangle will be considered front-facing if its vertices are counter-clockwise on the render target
		bool m_TriangleFrontIsCounterClockwise = false;
	};

	struct StencilState
	{
		EComparisonFunction m_StencilFunc = EComparisonFunction::Always;
		EStencilOperation m_StencilFailOp = EStencilOperation::Keep;
		EStencilOperation m_DepthFailOp = EStencilOperation::Keep;
		EStencilOperation m_StencilOp = EStencilOperation::Keep;

		uint32_t m_ReferenceValue = 0;
		uint8_t m_StencilMask = 0b11111111;
	};

	struct DepthStencilState
	{
		bool m_EnableDepthTest = true;
		EComparisonFunction m_ComparisonFunction = EComparisonFunction::Less;
		StencilState m_FrontStencilState;
		StencilState m_BackStencilState;
	};

	enum class EInstanceDataStepClassification : uint8_t
	{
		// Vertex input changes for each vertex
		PerVertex,
		// Vertex input changes for each instance
		PerInstance
	};

	// https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_input_element_desc
	struct VertexInputElement
	{
		// The index of the vertex buffer to read this input element from
		uint8_t m_InputSlot = 0;
		uint8_t m_SemanticIndex = 0;
		const char* m_SemanticName = nullptr;
		// The format in which the vertex input element is stored
		EFormat m_Format = EFormat::Unknown;

		// Indicates how often the data read from the vertex buffer advances to the next element
		EInstanceDataStepClassification m_InstanceDataStepClassification = EInstanceDataStepClassification::PerVertex;
		// The number of instances to draw using the same per-instance data before advancing to the next element in the vertex buffer. Must be 0 when advancing once per vertex.
		uint8_t m_InstanceDataStepRate = 0;
	};

	struct VertexInputLayout
	{
		static constexpr size_t MaxInputElements = 8;

		tabi::array<VertexInputElement, MaxInputElements> m_InputElements{};
		uint8_t m_NumInputElements = 0;
	};

	struct GraphicsPipelineDescription
	{
		static constexpr size_t MaxBlendTargets = 8;

		const class Shader* m_VertexShader = nullptr;
		const class Shader* m_PixelShader = nullptr;

		ETopology m_Topology = ETopology::Triangle;
		// If false, the first blend state will be used for all blend targets
		bool m_IndividualBlend = false;
		tabi::array<BlendState, MaxBlendTargets> m_BlendState;
		RasterizerState m_RasterizerState;
		DepthStencilState m_DepthStencilState;
		VertexInputLayout m_VertexInputLayout;
	};

	class GraphicsPipeline
	{
	public:
		TABI_NO_COPY(GraphicsPipeline);
		TABI_NO_MOVE(GraphicsPipeline);

		inline const GraphicsPipelineDescription& GetPipelineDescription() const
		{
			return m_PipelineDescription;
		}

	protected:
		GraphicsPipeline(const GraphicsPipelineDescription& a_PipelineDescription)
			: m_PipelineDescription(a_PipelineDescription)
		{
			TABI_ASSERT(a_PipelineDescription.m_VertexShader && a_PipelineDescription.m_VertexShader->GetShaderType() == EShaderType::Vertex);
			TABI_ASSERT(a_PipelineDescription.m_PixelShader && a_PipelineDescription.m_PixelShader->GetShaderType() == EShaderType::Pixel);
		}
		~GraphicsPipeline() = default;

	private:
		GraphicsPipelineDescription m_PipelineDescription;
	};
}
