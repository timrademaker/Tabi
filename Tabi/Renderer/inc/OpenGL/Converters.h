#pragma once

#include "Enums/Format.h"
#include "Enums/ShaderEnums.h"
#include "Enums/TextureEnums.h"

#include <glad/glad.h>

namespace tabi
{
	GLenum GLTextureDimension(ETextureDimension a_Dimension);
	GLenum GLShaderType(EShaderType a_ShaderType);
}
