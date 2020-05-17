#include "IFile.h"

#include <Logging.h>

#if defined(_WINDOWS)
#include "Windows/FileWindows.h"
#endif

using namespace tabi;

tabi::unique_ptr<IFile> tabi::IFile::OpenFile(const char* a_FilePath, const EFileOpenFlags a_OpenFlags)
{
    auto file = tabi::make_unique<File>();

    auto result = file->Open(a_FilePath, a_OpenFlags);
    if ((result & EFileResult::Ok) != EFileResult::Ok)
    {
        logger::TabiLog(logger::ELogLevel::Warning, "Unable to open file \"" + tabi::string(a_FilePath) + "\"");
    }

    return std::move(file);
}