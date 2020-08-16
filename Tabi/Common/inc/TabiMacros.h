#pragma once

#define TABI_EXPORT
#define TABI_INLINE inline
#define TABI_NODISCARD

// if constexpr (condition) is c++17 and up
#define TABI_CONSTEXPR_IF

#define TABI_UNUSED(var) (var)

#define TABI_ASSERT(expression) assert(expression)

#define TABI_BIND(Object, Function)             std::bind(&Function, Object)
#define TABI_BIND_OneParam(Object, Function)    std::bind(&Function, Object, std::placeholders::_1)

#if defined(_MSC_VER)
#define DISABLE_WARNING_PUSH __pragma(warning(push))
#define DISABLE_WARNING_POP __pragma(warning(pop))
#define DISABLE_WARNING(warningNumber) __pragma(warning( disable : warningNumber ))

#define DISABLE_NAMELESS_STRUCT_WARNING DISABLE_WARNING(4201)
#define DISABLE_SIGNED_UNSIGNED_MISMATCH_WARNING DISABLE_WARNING(4245)
#define DISABLE_POSSIBLE_LOSS_OF_DATA_WARNING DISABLE_WARNING(4267)
#define DISABLE_ALL_WARNINGS __pragma(warning(push, 0))

#elif defined(__GNUC__) || defined(__clang__)
#define DO_PRAGMA(X) _Pragma(#X)
#define DISABLE_WARNING_PUSH           DO_PRAGMA(GCC diagnostic push)
#define DISABLE_WARNING_POP            DO_PRAGMA(GCC diagnostic pop) 
#define DISABLE_WARNING(warningName)   DO_PRAGMA(GCC diagnostic ignored #warningName)

#endif