#pragma once

#include <TabiMacros.h>
#include "Enums/ComparisonFunction.h"

namespace tabi
{
	enum class EToplolgy : uint8_t
	{
		Point,
		Line,
		LineStrip,
		Triangle,
		TriangleStrip,
	};

	enum class EBlendFactor : uint8_t
	{
		Zero,
		One,
		SrcAlpha,
		DstAlpha,
		InvSrcAlpha,
		InvDstAlpha,
		SrcColor,
		DstColor,
		InvSrcColor,
		InvDstColor,
		SrcAlpha
	};

	enum class EBlendFunction : uint8_t
	{
		Add,
		Subtract,
		ReverseSubtract,
		Min,
		Max
	};

	enum class EPolygonMode : uint8_t
	{
		Point,
		Line,
		Fill
	};

	enum class ECullMode : uint8_t
	{
		None,
		Front,
		Back
	};

	enum class EColorMask : uint8_t
	{
		Red = 1 << 0,
		Green = 1 << 1,
		Blue = 1 << 2,
		Alpha = 1 << 3,
		All = Red | Green | Blue | Alpha
	};
	TABI_ENUM_FLAG(EColorMask);

	enum class EStencilOperation : uint8_t
	{
		Zero,
		Keep,
		Replace,
		Increment,
		Decrement,
		Invert.
		IncrementWrap,
		DecrementWrap
	};

	struct BlendState
	{
		bool m_BlendEnabled = false;
		EBlendFactor m_SourceBlendFactorRGB = EBlendFactor::One;
		EBlendFactor m_DestBlendFactorRGB = EBlendFactor::Zero;
		EBlendFunction m_BlendFunctionRGB = EBlendFunction::Add;

		EBlendFactor m_SourceBlendFactorAlpha = EBlendFactor::One;
		EBlendFactor m_DestBlendFactorAlpha = EBlendFactor::Zero;
		EBlendFunction m_BlendFunctionAlpha = EBlendFunction::Add;
	};

	struct RasterizerState
	{
		EPolygonMode m_PolygonMode = EPolygonMode::Fill;
		ECullMode m_CullMode = ECullMode::Back;

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
		uint8_t m_StencilMask = 255;
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
		uint8_t m_InputSlot = 0;
		uint8_t m_NumComponents = 0;
		uint8_t m_SemanticIndex = 0;
		const char* m_SemanticName = nullptr;

		// Indicates how often the data read from the vertex buffer advances to the next element
		EInstanceDataStepClassification m_InstanceDataStepClassification = EInstanceDataStepClassification::PerVertex;
		// The number of instances to draw using the same per-instance data before advancing to the next element in the vertex buffer. Must be 0 when advancing once per vertex.
		uint8_t m_InstanceDataStepRate = 0;
	};

	struct VertexInputLayout
	{
		std::vector<VertexInputElement> m_InputElements{};
		uint8_t m_NumInputElements = 0;
	};

	struct GraphicsPipelineDescription
	{
		class IShader* m_VertexShader = nullptr;
		class IShader* m_PixelShader = nullptr;

		EToplolgy m_Topology = EToplolgy::Triangle;
		// TODO: Support multiple blend targets?
		BlendState m_BlendState;
		RasterizerState m_RasterizerState;
		DepthStencilState m_DepthStencilState;
		VertexInputLayout m_VertexInputLayout;
	};

	class GraphicsPipeline
	{
	public:
		inline const GraphicsPipelineDescription& GetPipelineDescription() const
		{
			return m_PipelineDescription;
		}

	protected:
		GraphicsPipeline(const GraphicsPipelineDescription& a_PipelineDescription)
			: m_PipelineDescription(a_PipelineDescription)
		{}

	private:
		GraphicsPipelineDescription m_PipelineDescription;
	};
}
