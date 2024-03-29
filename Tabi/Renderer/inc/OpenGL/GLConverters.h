#pragma once

#include "Enums/BufferEnums.h"
#include "Enums/ComparisonFunction.h"
#include "Enums/Format.h"
#include "Enums/GraphicsPipelineEnums.h"
#include "Enums/ShaderEnums.h"
#include "Enums/SamplerEnums.h"
#include "Enums/TextureEnums.h"

#include <TabiTypes.h>

#include <glad/gl.h>

namespace tabi
{
	GLenum GLTextureDimension(ETextureDimension a_Dimension);

	GLenum GLFormat(EFormat a_Format);
	GLenum GLInternalFormat(EFormat a_Format);
	GLenum GLType(EDataType a_DataType);

	GLenum GLShaderType(EShaderType a_ShaderType);
	GLenum GLCubeMapFace(ECubeMapFace a_Face);

	GLenum GLTarget(ETextureDimension a_TextureDimension);
	GLenum GLTarget(EBufferRole a_BufferRole);

	GLenum GLWrapMode(EWrapMode a_WrapMode);
	GLenum GLMinFilter(EFilterMode a_MinFilter, EMipMapMode a_MipMapMode);
	GLenum GLMagFilter(EFilterMode a_MagFilter);

	GLenum GLComparisonFunction(EComparisonFunction a_ComparisonFunction);
	GLenum GLStencilOperation(EStencilOperation a_StencilOperation);

	GLenum GLCullMode(ECullMode a_CullMode);
	GLenum GLPolygonMode(EPolygonMode a_PolygonMode);

	GLenum GLBlendEquation(EBlendOperation a_BlendOperation);
	GLenum GLBlendFactor(EBlendFactor a_BlendFactor);

	GLenum GLTopology(ETopology a_Topology);

	GLint GLCubeFaceToLayer(ETextureDimension a_TextureDimension, uint8_t a_Layer, ECubeMapFace a_Face);

	tabi::string GLDebugMessageSource(GLenum a_Source);
	tabi::string GLDebugMessageType(GLenum a_Type);
}
