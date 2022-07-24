#pragma once

#include "Enums/Format.h"
#include "Enums/ShaderEnums.h"
#include "Enums/TextureEnums.h"

#include <glad/glad.h>

namespace tabi
{
	GLenum GLTextureDimension(ETextureDimension a_Dimension);
	GLenum GLFormat(EFormat a_Format);
	GLenum GLInternalFormat(EFormat a_Format);
	GLenum GLType(EFormat a_Format);
	GLenum GLShaderType(EShaderType a_ShaderType);
	GLenum GLCubeMapFace(ECubemapFace a_Face);
}
