#pragma once

#define TABI_EXPORT
#define TABI_INLINE inline
#define TABI_NODISCARD

// if constexpr (condition) is c++17 and up
#define TABI_CONSTEXPR_IF

#define TABI_UNUSED(var) (var)