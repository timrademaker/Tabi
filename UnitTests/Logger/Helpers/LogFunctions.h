#include "TabiTypes.h"

namespace tabi
{
    namespace logger
    {
        class Logger;
    }
}

namespace testlog
{
    void LogToAllLevels(::tabi::logger::Logger* logger, const tabi::string& a_Message);
}
