#pragma once

#if defined(_DEBUG)
#include <cassert>
#endif

#define TABI_EXPORT
#define TABI_INLINE inline
#define TABI_NODISCARD

#define TABI_UNUSED(var) (var)

#if defined(_DEBUG)
#define TABI_ASSERT(expression, ...) assert(expression)
#else
#define TABI_ASSERT(expression) if(!(expression)) __debugbreak()
#endif

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

#define TABI_ENUM_FLAG(EnumName) inline EnumName operator|(const EnumName& a_Lhs, const EnumName& a_Rhs) { return static_cast<EnumName>(static_cast<int64_t>(a_Lhs) | static_cast<int64_t>(a_Rhs)); } \
inline EnumName operator|=(EnumName& a_Lhs, const EnumName& a_Rhs) { a_Lhs = static_cast<EnumName>(a_Lhs | a_Rhs);  return a_Lhs; } \
inline EnumName operator&(const EnumName& a_Lhs, const EnumName& a_Rhs) { return static_cast<EnumName>(static_cast<int64_t>(a_Lhs) & static_cast<int64_t>(a_Rhs)); }

#define TABI_NO_COPY(ClassName) ClassName(ClassName&) = delete; \
ClassName(const ClassName&) = delete; \
ClassName& operator=(const ClassName&) = delete;

#define TABI_NO_MOVE(ClassName) ClassName(ClassName&&) = delete; \
ClassName& operator=(ClassName&&) = delete;
