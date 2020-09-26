#pragma once

#include <memory>

namespace tabi
{
    template<typename T>
    using weak_ptr = std::weak_ptr<T>;

    template<typename T>
    using shared_ptr = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    inline auto make_shared(Args&&... a_Args)
    {
        return std::make_shared<T>(tabi::forward<Args>(a_Args)...);
    }

    template<typename T>
    using unique_ptr = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    inline auto make_unique(Args&&... a_Args)
    {
        return std::make_unique<T>(tabi::forward<Args>(a_Args)...);
    }


    // Forward
    template<typename T, typename ... Args>
    inline constexpr auto forward(Args&&... a_Args)
    {
        return std::forward<T>(std::forward<Args>(a_Args)...);
    }

    // Static pointer cast
    template<typename _Ty1, typename _Ty2>
    inline tabi::shared_ptr<_Ty1> static_pointer_cast(const tabi::shared_ptr<_Ty2>& a_Other)
    {
        return std::static_pointer_cast<_Ty1>(a_Other);
    }

    template<typename _Ty1, typename _Ty2>
    inline tabi::shared_ptr<_Ty1> static_pointer_cast(tabi::shared_ptr<_Ty2>&& a_Other)
    {
        return std::static_pointer_cast<_Ty1>(a_Other);
    }
}