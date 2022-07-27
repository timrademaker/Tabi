#include "Helpers/FormatInfo.h"

#include <TabiContainers.h>

namespace tabi
{
	class FormatInfoTable
	{
	public:
		tabi::array<FormatInfo, static_cast<size_t>(EFormat::Count)> m_Table;

		void Add(EFormat a_Format, FormatInfo a_FormatInfo)
		{
			m_Table[static_cast<size_t>(a_Format)] = std::move(a_FormatInfo);
		}

		FormatInfoTable()
		{

			Add(EFormat::RGBA32_float,		{ false, 32, 4 });
			Add(EFormat::RGBA32_uint, { false, 32, 4 });
			Add(EFormat::RGBA32_sint,		{ false, 32, 4 });
			Add(EFormat::RGB32_float,		{ false, 32, 3 });
			Add(EFormat::RGB32_uint,		{ false, 32, 3 });
			Add(EFormat::RGB32_sint,		{ false, 32, 3 });
			Add(EFormat::RG32_float,		{ false, 32, 2 });
			Add(EFormat::RG32_uint,			{ false, 32, 2 });
			Add(EFormat::RG32_sint,			{ false, 32, 2 });
			Add(EFormat::R32_float,			{ false, 32, 1 });
			Add(EFormat::R32_uint,			{ false, 32, 1 });
			Add(EFormat::R32_sint,			{ false, 32, 1 });
			Add(EFormat::RGBA16_float,		{ false, 16, 4 });
			Add(EFormat::RGBA16_unorm,		{ true, 16, 4 });
			Add(EFormat::RGBA16_snorm,		{ true, 16, 4 });
			Add(EFormat::RGBA16_uint,		{ false, 16, 4 });
			Add(EFormat::RGBA16_sint,		{ false, 16, 4 });
			Add(EFormat::RGB16_float,		{ false, 16, 4 });
			Add(EFormat::RGB16_unorm,		{ true, 16, 3 });
			Add(EFormat::RGB16_snorm,		{ true, 16, 3 });
			Add(EFormat::RGB16_uint,		{ false, 16, 3 });
			Add(EFormat::RGB16_sint,		{ false, 16, 3 });
			Add(EFormat::RG16_float,		{ false, 16, 2 });
			Add(EFormat::RG16_unorm,		{ true, 16, 2 });
			Add(EFormat::RG16_snorm,		{ true, 16, 2 });
			Add(EFormat::RG16_uint,			{ false, 16, 2 });
			Add(EFormat::RG16_sint,			{ false, 16, 2 });
			Add(EFormat::R16_float,			{ false, 16, 1 });
			Add(EFormat::R16_unorm,			{ true, 16, 1 });
			Add(EFormat::R16_snorm,			{ true, 16, 1 });
			Add(EFormat::R16_uint,			{ false, 16, 1 });
			Add(EFormat::R16_sint,			{ false, 16, 1 });
			Add(EFormat::RGBA8_unorm,		{ true, 8, 4 });
			Add(EFormat::RGBA8_snorm,		{ true, 8, 4 });
			Add(EFormat::RGBA8_uint,		{ false, 8, 4 });
			Add(EFormat::RGBA8_sint,		{ false, 8, 4 });
			Add(EFormat::RGB8_unorm,		{ true, 8, 3 });
			Add(EFormat::RGB8_snorm,		{ true, 8, 3 });
			Add(EFormat::RGB8_uint,			{ false, 8, 3 });
			Add(EFormat::RGB8_sint,			{ false, 8, 3 });
			Add(EFormat::RG8_unorm,			{ true, 8, 2 });
			Add(EFormat::RG8_snorm,			{ true, 8, 2 });
			Add(EFormat::RG8_uint,			{ false, 8, 2 });
			Add(EFormat::RG8_sint,			{ false, 8, 2 });
			Add(EFormat::R8_unorm,			{ true, 8, 1 });
			Add(EFormat::R8_snorm,			{ true, 8, 1 });
			Add(EFormat::R8_uint,			{ false, 8, 1 });
			Add(EFormat::R8_sint,			{ false, 8, 1 });
			Add(EFormat::Depth16,			{ false, 16, 1 });
			Add(EFormat::Depth24,			{ false, 24, 1 });
			Add(EFormat::Depth32_float,		{ false, 32, 1 });
			Add(EFormat::Depth24Stencil8,	{ false, 32, 2 });	// Why does this need two different component sizes again?
		}
	};
}

const tabi::FormatInfo& tabi::GetFormatInfo(EFormat a_Format)
{
	static const FormatInfoTable table;

	return table.m_Table[static_cast<size_t>(a_Format)];
}
