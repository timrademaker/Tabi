#pragma once

namespace tabi
{
	enum class EShaderType : int8_t
	{
		None = -1,
		Vertex,
		Pixel,
		Compute
	};

	struct ShaderDescription
	{
		EShaderType m_ShaderType = EShaderType::None;
		const char* m_Data = nullptr;
	};

	class IShader
	{
	public:
		IShader(EShaderType a_ShaderType) : m_ShaderType(a_ShaderType){};

		EShaderType GetShaderType() const
		{
			return m_ShaderType;
		}

	protected:
		EShaderType m_ShaderType = EShaderType::None;
		
	};
}
