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
        TABI_WARN( "Unable to open file \"%s\"", a_FilePath);
        return nullptr;
    }

    return std::move(file);
}

bool tabi::IFile::IsSuccess(const EFileResult& a_Result)
{
    return ((a_Result & EFileResult::Ok) == EFileResult::Ok);
}