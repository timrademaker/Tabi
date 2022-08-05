#pragma once

#include <cstdint>

namespace tabi
{
	enum class EShaderType : int8_t
	{
		Invalid = -1,
		Vertex,
		Pixel,
		Compute
	};
}
