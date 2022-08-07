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
            Add(EFormat::RGBA32_float,      { false,    16,    4,    EDataType::Float   });
            Add(EFormat::RGBA32_uint,       { false,    16,    4,    EDataType::Uint    });
            Add(EFormat::RGBA32_sint,       { false,    16,    4,    EDataType::Int     });
            Add(EFormat::RGB32_float,       { false,    12,    3,    EDataType::Float   });
            Add(EFormat::RGB32_uint,        { false,    12,    3,    EDataType::Uint    });
            Add(EFormat::RGB32_sint,        { false,    12,    3,    EDataType::Int     });
            Add(EFormat::RG32_float,        { false,     8,    2,    EDataType::Float   });
            Add(EFormat::RG32_uint,         { false,     8,    2,    EDataType::Uint    });
            Add(EFormat::RG32_sint,         { false,     8,    2,    EDataType::Int     });
            Add(EFormat::R32_float,         { false,     4,    1,    EDataType::Float   });
            Add(EFormat::R32_uint,          { false,     4,    1,    EDataType::Uint    });
            Add(EFormat::R32_sint,          { false,     4,    1,    EDataType::Int     });
            Add(EFormat::RGBA16_float,      { false,     8,    4,    EDataType::Float   });
            Add(EFormat::RGBA16_unorm,      { true,      8,    4,    EDataType::Uint    });
            Add(EFormat::RGBA16_snorm,      { true,      8,    4,    EDataType::Int     });
            Add(EFormat::RGBA16_uint,       { false,     8,    4,    EDataType::Uint    });
            Add(EFormat::RGBA16_sint,       { false,     8,    4,    EDataType::Int     });
            Add(EFormat::RGB16_float,       { false,     6,    4,    EDataType::Float   });
            Add(EFormat::RGB16_unorm,       { true,      6,    3,    EDataType::Uint    });
            Add(EFormat::RGB16_snorm,       { true,      6,    3,    EDataType::Int     });
            Add(EFormat::RGB16_uint,        { false,     6,    3,    EDataType::Uint    });
            Add(EFormat::RGB16_sint,        { false,     6,    3,    EDataType::Int     });
            Add(EFormat::RG16_float,        { false,     4,    2,    EDataType::Float   });
            Add(EFormat::RG16_unorm,        { true,      4,    2,    EDataType::Uint    });
            Add(EFormat::RG16_snorm,        { true,      4,    2,    EDataType::Int     });
            Add(EFormat::RG16_uint,         { false,     4,    2,    EDataType::Uint    });
            Add(EFormat::RG16_sint,         { false,     4,    2,    EDataType::Int     });
            Add(EFormat::R16_float,         { false,     2,    1,    EDataType::Float   });
            Add(EFormat::R16_unorm,         { true,      2,    1,    EDataType::Uint    });
            Add(EFormat::R16_snorm,         { true,      2,    1,    EDataType::Int     });
            Add(EFormat::R16_uint,          { false,     2,    1,    EDataType::Uint    });
            Add(EFormat::R16_sint,          { false,     2,    1,    EDataType::Int     });
            Add(EFormat::RGBA8_unorm,       { true,      4,    4,    EDataType::Ubyte   });
            Add(EFormat::RGBA8_snorm,       { true,      4,    4,    EDataType::Byte    });
            Add(EFormat::RGBA8_uint,        { false,     4,    4,    EDataType::Ubyte   });
            Add(EFormat::RGBA8_sint,        { false,     4,    4,    EDataType::Byte    });
            Add(EFormat::RGB8_unorm,        { true,      3,    3,    EDataType::Ubyte   });
            Add(EFormat::RGB8_snorm,        { true,      3,    3,    EDataType::Byte    });
            Add(EFormat::RGB8_uint,         { false,     3,    3,    EDataType::Ubyte   });
            Add(EFormat::RGB8_sint,         { false,     3,    3,    EDataType::Byte    });
            Add(EFormat::RG8_unorm,         { true,      2,    2,    EDataType::Ubyte   });
            Add(EFormat::RG8_snorm,         { true,      2,    2,    EDataType::Byte    });
            Add(EFormat::RG8_uint,          { false,     2,    2,    EDataType::Ubyte   });
            Add(EFormat::RG8_sint,          { false,     2,    2,    EDataType::Byte    });
            Add(EFormat::R8_unorm,          { true,      1,    1,    EDataType::Ubyte   });
            Add(EFormat::R8_snorm,          { true,      1,    1,    EDataType::Byte    });
            Add(EFormat::R8_uint,           { false,     1,    1,    EDataType::Ubyte   });
            Add(EFormat::R8_sint,           { false,     1,    1,    EDataType::Byte    });
            Add(EFormat::Depth16_unorm,     { true,      2,    1,    EDataType::Ushort  });
            Add(EFormat::Depth32_float,     { false,     4,    1,    EDataType::Float   });
            Add(EFormat::Depth24Stencil8,   { false,     4,    2,    EDataType::Int24_8 });
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
