#pragma once

#include <TabiTypes.h>
#include <TabiMacros.h>

namespace tabi
{
    using files::FH;
    using files::FSize;

    enum class EFileOpenFlags
    {
        None = (0U << 0),
        Read = (1U << 0),
        Write = (1U << 1),
        ReadWrite = (Read | Write),
        Create = (1U << 2),
        Append = (1U << 3),
        Overwrite = (1U << 4),
        Binary = (1U << 5)
    };
    TABI_ENUM_FLAG(EFileOpenFlags);

    enum class EFileResult
    {
        Ok = 1 << 1,
        Failed = 1 << 2,
        InvalidOpenFlags = 1 << 3,
        InvalidFileHandle = 1 << 4,
        EndOfFileReached = 1 << 5,
        FileNotFound = 1 << 6,
    };
    TABI_ENUM_FLAG(EFileResult);

    enum class EFileSeekOrigin
    {
        Begin = 1 << 1,
        Current = 1 << 2,
        End = 1 << 3
    };


    class IFile
    {
    public:
        IFile() = default;
        virtual ~IFile() = default;

        /**
        * @brief Opens a file
        * @param a_FilePath The path to the file
        * @param a_OpenFlags One or more EFileOpenFlags, specifying how the file will be used
        * @returns A pointer to the opened file. Can be nullptr.
        */
        static tabi::unique_ptr<IFile> OpenFile(const char* a_FilePath, const EFileOpenFlags a_OpenFlags);

        static bool IsSuccess(const EFileResult& a_Result);

        virtual EFileResult Close(const bool a_CancelPendingOperations = false) = 0;
        virtual EFileResult Read(char* a_ReadBuffer, FSize a_BufferSize, FSize* a_BytesRead = nullptr) = 0;
        virtual EFileResult Write(const char* a_WriteBuffer, FSize a_BufferSize) = 0;
        virtual EFileResult Seek(const EFileSeekOrigin a_SeekOrigin, FSize a_SeekPos, FSize* a_NewPosition = nullptr) = 0;
        virtual EFileResult GetLength(FSize& a_FileLength) = 0;

    protected:
        virtual EFileResult Open(const char* a_FilePath, const EFileOpenFlags a_OpenFlags) = 0;
    };
}