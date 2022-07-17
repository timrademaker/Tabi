#pragma once

namespace tabi
{
	enum class EShaderType : int8_t
	{
		Invalid = -1,
		Vertex,
		Pixel,
		Compute
	};

	struct ShaderDescription
	{
		EShaderType m_ShaderType = EShaderType::Invalid;
		const char* m_Data = nullptr;
		uint32_t m_DataLength = 0;
	};

	class IShader
	{
	public:
		IShader(EShaderType a_ShaderType)
			: m_ShaderType(a_ShaderType)
		{};

		inline EShaderType GetShaderType() const
		{
			return m_ShaderType;
		}

	private:
		EShaderType m_ShaderType = EShaderType::Invalid;
		
	};
}
