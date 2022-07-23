#pragma once

#include "Enums/ShaderEnums.h"

namespace tabi
{
	struct ShaderDescription
	{
		EShaderType m_ShaderType = EShaderType::Invalid;
		const char* m_Data = nullptr;
		uint32_t m_DataLength = 0;
	};

	class Shader
	{
	public:
		inline EShaderType GetShaderType() const
		{
			return m_ShaderType;
		}

	protected:
		Shader(EShaderType a_ShaderType)
			: m_ShaderType(a_ShaderType)
		{};

	private:
		EShaderType m_ShaderType = EShaderType::Invalid;
		
	};
}