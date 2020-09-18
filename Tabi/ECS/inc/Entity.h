#pragma once

#include <bitset>

namespace tabi
{
    constexpr size_t MAX_COMPONENTS = 32;

    using Entity = size_t;
    using EntitySignature = std::bitset<MAX_COMPONENTS>;
}