#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>

#if defined(_WINDOWS)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace tabi
{
    // Container types
    using string = std::string;
    
    template<typename T>
    using vector = std::vector<T>;
    
    template<typename Key, typename T>
    using map = std::map<Key, T>;

    template<typename Key, typename T>
    using unordered_map = std::unordered_map<Key, T>;


    // Smart pointers
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

    namespace graphics
    {
        using WindowHandle = HWND;
    }
}