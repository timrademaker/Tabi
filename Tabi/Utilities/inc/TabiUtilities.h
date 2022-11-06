#pragma once

#include <TabiTypes.h>

namespace tabi
{
    namespace utils
    {
        /**
        * @brief Replaces all occurrences of a substring in a string
        * @params a_String The string in which a substring should be replaced
        * @params a_Search The substring to replace
        * @params a_Replacement The string to replace the substring with
        * @returns A string with all occurrences of a_Search replaced
        */
        tabi::string StringReplace(const tabi::string& a_String, const tabi::string& a_Search, const tabi::string& a_Replacement);

        tabi::resources::ResourceID CalculateResourceID(const char* a_FilePath);
    }
}