#include "TabiUtilities.h"

using namespace tabi;


////////////////////////////////////////////////////////////////////////////////
// Courtesy of: http://stackoverflow.com/questions/5878775/how-to-find-and-replace-string
////////////////////////////////////////////////////////////////////////////////
tabi::string tabi::utils::StringReplace(const tabi::string& a_String, const tabi::string& a_Search, const tabi::string& a_Replacement)
{
    tabi::string result(a_String);
    size_t pos = 0;

    while ((pos = result.find(a_Search, pos)) != tabi::string::npos)
    {
        result.replace(pos, a_Search.length(), a_Replacement);
        pos += a_Replacement.length();
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// String hashing function
// Taken from http://www.cse.yorku.ca/~oz/hash.html (public domain)
////////////////////////////////////////////////////////////////////////////////
tabi::resources::ResourceID tabi::utils::CalculateResourceID(const char* a_FilePath)
{
    resources::ResourceID hash = 0;
    int c = *a_FilePath++;

    while (c)
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
        c = *a_FilePath++;
    }

    return hash;
}