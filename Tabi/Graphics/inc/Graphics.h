#pragma once

#include <Enums/ShaderEnums.h>

namespace tabi
{
	class Shader;

	namespace graphics
	{
		void BeginFrame();
		void EndFrame();

		tabi::Shader* LoadShader(const char* a_ShaderPath, tabi::EShaderType a_ShaderType, const char* a_DebugName);
	}
}
