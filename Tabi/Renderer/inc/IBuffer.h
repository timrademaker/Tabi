#pragma once

#include "Format.h"

namespace tabi
{
	struct BufferDescription
	{
		EFormat m_Format = EFormat::Unknown;
		size_t m_SizeInBytes = 0;
		uint32_t m_Stride = 0;
	};

	class IBuffer
	{
		
	};
}
