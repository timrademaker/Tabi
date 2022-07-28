#include "Helpers/FormatInfo.h"

#include <TabiContainers.h>
#include <TabiMacros.h>

namespace tabi
{
	class FormatInfoTable
	{
	public:
		FormatInfoTable()
		{

			Add(EFormat::RGBA32_float,		{ false,	128,	4, EDataType::Float		});
			Add(EFormat::RGBA32_uint,		{ false,	128,	4, EDataType::Uint		});
			Add(EFormat::RGBA32_sint,		{ false,	128,	4, EDataType::Int		});
			Add(EFormat::RGB32_float,		{ false,	 96,	3, EDataType::Float		});
			Add(EFormat::RGB32_uint,		{ false,	 96,	3, EDataType::Uint		});
			Add(EFormat::RGB32_sint,		{ false,	 96,	3, EDataType::Int		});
			Add(EFormat::RG32_float,		{ false,	 64,	2, EDataType::Float		});
			Add(EFormat::RG32_uint,			{ false,	 64,	2, EDataType::Uint		});
			Add(EFormat::RG32_sint,			{ false,	 64,	2, EDataType::Int		});
			Add(EFormat::R32_float,			{ false,	 32,	1, EDataType::Float		});
			Add(EFormat::R32_uint,			{ false,	 32,	1, EDataType::Uint		});
			Add(EFormat::R32_sint,			{ false,	 32,	1, EDataType::Int		});
			Add(EFormat::RGBA16_float,		{ false,	 64,	4, EDataType::Float		});
			Add(EFormat::RGBA16_unorm,		{ true,		 64,	4, EDataType::Uint		});
			Add(EFormat::RGBA16_snorm,		{ true,		 64,	4, EDataType::Int		});
			Add(EFormat::RGBA16_uint,		{ false,	 64,	4, EDataType::Uint		});
			Add(EFormat::RGBA16_sint,		{ false,	 64,	4, EDataType::Int		});
			Add(EFormat::RGB16_float,		{ false,	 48,	4, EDataType::Float		});
			Add(EFormat::RGB16_unorm,		{ true,		 48,	3, EDataType::Uint		});
			Add(EFormat::RGB16_snorm,		{ true,		 48,	3, EDataType::Int		});
			Add(EFormat::RGB16_uint,		{ false,	 48,	3, EDataType::Uint		});
			Add(EFormat::RGB16_sint,		{ false,	 48,	3, EDataType::Int		});
			Add(EFormat::RG16_float,		{ false,	 32,	2, EDataType::Float		});
			Add(EFormat::RG16_unorm,		{ true,		 32,	2, EDataType::Uint		});
			Add(EFormat::RG16_snorm,		{ true,		 32,	2, EDataType::Int		});
			Add(EFormat::RG16_uint,			{ false,	 32,	2, EDataType::Uint		});
			Add(EFormat::RG16_sint,			{ false,	 32,	2, EDataType::Int		});
			Add(EFormat::R16_float,			{ false,	 16,	1, EDataType::Float		});
			Add(EFormat::R16_unorm,			{ true,		 16,	1, EDataType::Uint		});
			Add(EFormat::R16_snorm,			{ true,		 16,	1, EDataType::Int		});
			Add(EFormat::R16_uint,			{ false,	 16,	1, EDataType::Uint		});
			Add(EFormat::R16_sint,			{ false,	 16,	1, EDataType::Int		});
			Add(EFormat::RGBA8_unorm,		{ true,		 32,	4, EDataType::Ubyte		});
			Add(EFormat::RGBA8_snorm,		{ true,		 32,	4, EDataType::Byte		});
			Add(EFormat::RGBA8_uint,		{ false,	 32,	4, EDataType::Ubyte		});
			Add(EFormat::RGBA8_sint,		{ false,	 32,	4, EDataType::Byte		});
			Add(EFormat::RGB8_unorm,		{ true,		 24,	3, EDataType::Ubyte		});
			Add(EFormat::RGB8_snorm,		{ true,		 24,	3, EDataType::Byte		});
			Add(EFormat::RGB8_uint,			{ false,	 24,	3, EDataType::Ubyte		});
			Add(EFormat::RGB8_sint,			{ false,	 24,	3, EDataType::Byte		});
			Add(EFormat::RG8_unorm,			{ true,		 16,	2, EDataType::Ubyte		});
			Add(EFormat::RG8_snorm,			{ true,		 16,	2, EDataType::Byte		});
			Add(EFormat::RG8_uint,			{ false,	 16,	2, EDataType::Ubyte		});
			Add(EFormat::RG8_sint,			{ false,	 16,	2, EDataType::Byte		});
			Add(EFormat::R8_unorm,			{ true,		  8,	1, EDataType::Ubyte		});
			Add(EFormat::R8_snorm,			{ true,		  8,	1, EDataType::Byte		});
			Add(EFormat::R8_uint,			{ false,	  8,	1, EDataType::Ubyte		});
			Add(EFormat::R8_sint,			{ false,	  8,	1, EDataType::Byte		});
			Add(EFormat::Depth16,			{ false,	 16,	1, EDataType::Ushort	});
			Add(EFormat::Depth32_float,		{ false,	 32,	1, EDataType::Float		});
			Add(EFormat::Depth24Stencil8,	{ false,	 32,	2, EDataType::Int24_8	});
		}

		const FormatInfo& GetFormatInfo(EFormat a_Format) const
		{
			const auto& info = m_Table[static_cast<size_t>(a_Format)];
			TABI_ASSERT(info.m_ComponentCount != 0, "Image format not set up in format info table");
			return info;
		}
		
	private:
		void Add(EFormat a_Format, FormatInfo a_FormatInfo)
		{
			m_Table[static_cast<size_t>(a_Format)] = std::move(a_FormatInfo);
		}

		tabi::array<FormatInfo, static_cast<size_t>(EFormat::Count)> m_Table;
	};
}

const tabi::FormatInfo& tabi::GetFormatInfo(EFormat a_Format)
{
	static const FormatInfoTable table;

	return table.GetFormatInfo(a_Format);
}
