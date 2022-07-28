#pragma once

#include "Enums/Format.h"

namespace tabi
{
	struct FormatInfo
	{
		bool m_IsNormalized = false;
		uint16_t m_FormatSizeInBits = 0;
		uint8_t m_ComponentCount = 0;

		EDataType m_DataType;
	};

	const FormatInfo& GetFormatInfo(EFormat a_Format);
}
