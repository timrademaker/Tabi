#pragma once

#include <memory>

namespace tabi
{
    template<typename T>
    using weak_ptr = std::weak_ptr<T>;

    template<typename T>
    using shared_ptr = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    auto make_shared(Args&&... a_Args)
    {
        return std::make_shared<T>(tabi::forward<Args>(a_Args)...);
    }

    template<typename T>
    using unique_ptr = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    auto make_unique(Args&&... a_Args)
    {
        return std::make_unique<T>(tabi::forward<Args>(a_Args)...);
    }


    // Forward
    template<typename T, typename ... Args>
    constexpr auto forward(Args&&... a_Args)
    {
        return std::forward<T>(std::forward<Args>(a_Args)...);
    }
}