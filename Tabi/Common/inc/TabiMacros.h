#pragma once

#define TABI_EXPORT
#define TABI_INLINE inline
#define TABI_NODISCARD

// if constexpr (condition) is c++17 and up
#define TABI_CONSTEXPR_IF

#define TABI_UNUSED(var) (var)

#if defined(_MSC_VER)
#define DISABLE_WARNING_PUSH __pragma(warning(push))
#define DISABLE_WARNING_POP __pragma(warning(pop))
#define DISABLE_WARNING(warningNumber) __pragma(warning( disable : warningNumber ))

#define DISABLE_NAMELESS_STRUCT_WARNING DISABLE_WARNING(4201)

#elif defined(__GNUC__) || defined(__clang__)
#define DO_PRAGMA(X) _Pragma(#X)
#define DISABLE_WARNING_PUSH           DO_PRAGMA(GCC diagnostic push)
#define DISABLE_WARNING_POP            DO_PRAGMA(GCC diagnostic pop) 
#define DISABLE_WARNING(warningName)   DO_PRAGMA(GCC diagnostic ignored #warningName)

#endif