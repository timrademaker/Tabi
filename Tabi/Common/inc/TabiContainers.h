#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

namespace tabi
{
    using string = std::string;

    template<typename T, typename allocator_t = typename std::vector<T>::allocator_type>
    using vector = std::vector<T, allocator_t>;

    template<typename key_t, typename T, class _Pr = std::less<key_t>, typename allocator_t = typename std::map<key_t, T>::allocator_type>
    using map = std::map<key_t, T, allocator_t>;

    template<typename key_t, typename T, typename hasher_t = std::hash<key_t>, typename keyeq_t = std::equal_to<key_t>, typename allocator_t = typename std::unordered_map<key_t, T>::allocator_type>
    using unordered_map = std::unordered_map<key_t, T, hasher_t, keyeq_t, allocator_t>;
}