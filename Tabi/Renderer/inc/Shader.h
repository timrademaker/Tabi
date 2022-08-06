#pragma once

#include "Enums/ShaderEnums.h"

#include <TabiMacros.h>

namespace tabi
{
	struct ShaderDescription
	{
		EShaderType m_ShaderType = EShaderType::Invalid;
		const char* m_Data = nullptr;
		size_t m_DataLength = 0;
	};

	class Shader
	{
	public:
		TABI_NO_COPY(Shader);
		TABI_NO_MOVE(Shader);

		inline EShaderType GetShaderType() const
		{
			return m_ShaderType;
		}

	protected:
		Shader(EShaderType a_ShaderType)
			: m_ShaderType(a_ShaderType)
		{};
		~Shader() = default;

	private:
		EShaderType m_ShaderType = EShaderType::Invalid;
	};
}
