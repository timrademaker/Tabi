#pragma once

#include <cstdint>

namespace tabi
{
	enum class EBufferRole : uint8_t
	{
		// Stores vertex data
		Vertex,
		// Stores vertex array indices
		Index,
		// Stores shader constants
		Constant,
	};
}
