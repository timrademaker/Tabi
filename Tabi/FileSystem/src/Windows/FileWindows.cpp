#include "Windows/FileWindows.h"

#include <Logging.h>

using namespace tabi;

tabi::File::~File()
{
    if (m_FileHandle)
    {
        Close();
    }
}

EFileResult tabi::File::Open(const char* a_FilePath, const EFileOpenFlags a_OpenFlags)
{
    std::fstream* file = new std::fstream;
    const OpenFlagType openFlags = ConvertOpenFlags(a_OpenFlags);

    if (openFlags == 0)
    {
        delete file;
        logger::TabiLog(logger::ELogLevel::Warning, "Error while opening file: Invalid open flags.");
        return EFileResult::InvalidOpenFlags;
    }

    // Check if file exists
    struct stat s;
    if (stat(a_FilePath, &s) < 0)
    {
        if ((a_OpenFlags & EFileOpenFlags::Create) != EFileOpenFlags::Create
            && (a_OpenFlags & EFileOpenFlags::Append) != EFileOpenFlags::Append
            && (a_OpenFlags & EFileOpenFlags::Overwrite) != EFileOpenFlags::Overwrite)
        {
            return EFileResult::Failed | EFileResult::FileNotFound;
        }
        else
        {
            // Make folders if needed
            std::string filePath(a_FilePath);
            size_t pos = 0;
            size_t prevPos = 0;

            std::string currentPath = "";

            constexpr const char pathSeparators[] = { '/', '\\' };

            for (auto separator : pathSeparators)
            {
                pos = 0;
                while ((pos = filePath.find(separator, pos)) != std::string::npos)
                {
                    // Get between pos and previous pos
                    char dir[32];
                    filePath.copy(dir, pos - prevPos, prevPos);
                    dir[pos - prevPos] = '\0';
                    pos += 1;
                    prevPos = pos;

                    currentPath += std::string(dir) + "/";

                    const auto dirresult = _mkdir(currentPath.c_str());
                    if (dirresult == -1)
                    {
                        if (errno == EEXIST)
                        {
                            logger::TabiLog(logger::ELogLevel::Info, "Directory " + currentPath + " not created as it already exists!");
                        }
                        else if (errno == ENOENT)
                        {
                            logger::TabiLog(logger::ELogLevel::Info, "Directory " + currentPath + " not found!");
                        }
                    }
                }
            }
        }
    }

    file->open(a_FilePath, openFlags);

    if (!file->is_open())
    {
        delete file;
        logger::TabiLog(logger::ELogLevel::Error, "Error while opening file: Unable to open file.");
        return EFileResult::Failed;
    }

    // Set file handle as the file has been opened successfully
    m_FileHandle = file;

    return EFileResult::Ok;
}

EFileResult tabi::File::Close(const bool a_CancelPendingOperations)
{
    TABI_UNUSED(a_CancelPendingOperations);

    if (!m_FileHandle)
    {
        logger::TabiLog(logger::ELogLevel::Info, "Trying to call close on a file that has already been closed!");
        return EFileResult::Ok;
    }
    m_FileHandle->flush();

    m_FileHandle->close();

    m_FileHandle = nullptr;

    return EFileResult::Ok;
}

EFileResult tabi::File::Read(char* a_ReadBuffer, FSize a_BufferSize, FSize* a_BytesRead)
{
    // Clear previous failure flags
    m_FileHandle->clear();

    if (!m_FileHandle->is_open())
    {
        logger::TabiLog(logger::ELogLevel::Warning, "Error while reading from file: The file isn't open!");
        return EFileResult::Failed;
    }

    FSize bytesRead = 0;
    EFileResult result = EFileResult::Ok;

    // Leave space for the null terminator
    while (bytesRead < a_BufferSize)
    {
        char nextChar;
        m_FileHandle->get(nextChar);
        if (m_FileHandle->eof())
        {
            result |= EFileResult::EndOfFileReached;
            break;
        }
        else
        {
            a_ReadBuffer[bytesRead] = nextChar;
        }

        ++bytesRead;
    }

    if (bytesRead + 1 < a_BufferSize)
    {
        a_ReadBuffer[bytesRead] = '\0';
    }

    if (a_BytesRead != nullptr)
    {
        *a_BytesRead = bytesRead;
    }

    m_FileHandle->flush();

    return result;
}

EFileResult tabi::File::Write(const char* a_WriteBuffer, FSize a_BufferSize)
{
    Seek(EFileSeekOrigin::Current, 0);
    m_FileHandle->write(a_WriteBuffer, a_BufferSize);

    if (!m_FileHandle->good())
    {
        logger::TabiLog(logger::ELogLevel::Error, "Error while writing to file: Something went wrong!");
        return EFileResult::Failed;
    }

    m_FileHandle->flush();

    return EFileResult::Ok;
}

EFileResult tabi::File::Seek(const EFileSeekOrigin a_SeekOrigin, FSize a_SeekPos, FSize* a_NewPosition)
{
    SeekOriginType seekFrom = ConvertSeekOrigin(a_SeekOrigin);

    // Clear previous flags
    m_FileHandle->clear();

    FSize fileLength = 0;
    {
        EFileResult result = GetLength(fileLength);
        if ((result & EFileResult::Ok) != EFileResult::Ok)
        {
            logger::TabiLog(logger::ELogLevel::Warning, "Error while seeking in file: Unable to get file length.");
            return result;
        }
    }

    // seekg and seekp are at the same position, so we only need to set one.
    m_FileHandle->seekg(static_cast<std::ios::seekdir>(a_SeekPos), seekFrom);

    if (!m_FileHandle->good())
    {
        logger::TabiLog(logger::ELogLevel::Warning, "Error while seeking in file: Something went wrong!");
        return EFileResult::Failed;
    }

    m_FileHandle->flush();

    auto result = EFileResult::Ok;
    if (m_FileHandle->tellg() >= fileLength)
    {
        m_FileHandle->seekg(0, std::ios::end);
        result |= EFileResult::EndOfFileReached;
    }

    if (a_NewPosition != nullptr)
    {
        *a_NewPosition = m_FileHandle->tellg();
    }

    return result;
}

EFileResult tabi::File::GetLength(FSize& a_FileLength)
{
    FSize startPosition = m_FileHandle->tellg();

    m_FileHandle->seekg(0, std::ios::end);
    a_FileLength = m_FileHandle->tellg();
    m_FileHandle->seekg(static_cast<std::ios::seekdir>(startPosition), std::ios::beg);

    return EFileResult::Ok;
}


File::OpenFlagType tabi::File::ConvertOpenFlags(const EFileOpenFlags a_OpenFlags) const
{
    File::OpenFlagType openFlags = 0;

    const EFileOpenFlags read = EFileOpenFlags::Read;
    const EFileOpenFlags write = EFileOpenFlags::Create | EFileOpenFlags::Write | EFileOpenFlags::Append;
    const EFileOpenFlags append = EFileOpenFlags::Append;
    const EFileOpenFlags truncate = EFileOpenFlags::Overwrite | EFileOpenFlags::Create;

    if ((a_OpenFlags & read) != EFileOpenFlags::None)
    {
        openFlags |= std::ios::in;
    }

    if ((a_OpenFlags & write) != EFileOpenFlags::None)
    {
        openFlags |= std::ios::out;
    }

    if ((a_OpenFlags & append) != EFileOpenFlags::None)
    {
        openFlags |= std::ios::app;
    }

    if ((a_OpenFlags & truncate) != EFileOpenFlags::None)
    {
        openFlags |= std::ios::trunc;
    }

    if ((a_OpenFlags & append) != EFileOpenFlags::None)
    {
        openFlags |= std::ios::ate;
    }

    if ((a_OpenFlags & EFileOpenFlags::Binary) != EFileOpenFlags::None)
    {
        openFlags |= std::ios::binary;
    }

    return openFlags;
}

File::SeekOriginType tabi::File::ConvertSeekOrigin(const EFileSeekOrigin a_SeekOrigin) const
{
    if (a_SeekOrigin == EFileSeekOrigin::Begin)
    {
        return std::ios_base::beg;
    }
    else if (a_SeekOrigin == EFileSeekOrigin::Current)
    {
        return std::ios_base::cur;
    }
    else if (a_SeekOrigin == EFileSeekOrigin::End)
    {
        return std::ios_base::end;
    }

    // If the seek origin is invalid, start seeking from the current location
    return std::ios_base::cur;
}