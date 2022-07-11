#pragma once

namespace tabi
{
	class IFence
	{
	public:
		virtual uint64_t GetFenceValue() = 0;
	};
}