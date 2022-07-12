#pragma once

#include <TabiMacros.h>

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

	enum class EComparisonFunction : uint8_t
	{
		Never,
		Less,
		Equal,
		LessOrEqual,
		Greater,
		GreaterOrEqual,
		NotEqual,
		Always
	};

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

	struct GraphicsPipelineDescription
	{
		class IShader* m_VertexShader = nullptr;
		class IShader* m_PixelShader = nullptr;

		EToplolgy m_Topology = EToplolgy::Triangle;
		// TODO: Support multiple blend targets?
		BlendState m_BlendState;
		RasterizerState m_RasterizerState;
		DepthStencilState m_DepthStencilState;
		// Vertex input format description
	};

	class IGraphicsPipeline
	{

	};
}
