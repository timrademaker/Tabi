#pragma once

#include "Enums/BufferEnums.h"
#include "Enums/Format.h"

namespace tabi
{
	struct BufferDescription
	{
		EFormat m_Format = EFormat::Unknown;
		EBufferRole m_Role = EBufferRole::Vertex;
		size_t m_SizeInBytes = 0;
		uint32_t m_Stride = 0;

		// TODO: Something about usage
		// OGL needs this when creating the buffer (glBufferData)
		// Might be related to this in D3D12? https://docs.microsoft.com/en-us/windows/win32/api/d3d12/ns-d3d12-d3d12_heap_properties
	};

	class Buffer
	{
	public:
		inline const BufferDescription& GetBufferDescription() const
		{
			return m_BufferDescription;
		}

	protected:
		Buffer(BufferDescription a_BufferDescription)
			: m_BufferDescription(a_BufferDescription)
		{}

	private:
		BufferDescription m_BufferDescription{};
	};
}
