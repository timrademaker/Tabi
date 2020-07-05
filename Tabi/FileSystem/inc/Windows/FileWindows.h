#pragma once

#include "IFile.h"

#include <fstream>
#include <iosfwd>

namespace tabi
{
    class File : public IFile
    {
        using FileType = std::fstream;
        using OpenFlagType = std::ios_base::openmode;
        using SeekOriginType = std::ios::seekdir;

    public:
        File() : m_FileHandle(0), m_FileLength(0) {}
        virtual ~File();

        virtual EFileResult Open(const char* a_FilePath, const EFileOpenFlags a_OpenFlags) override final;
        virtual EFileResult Close(const bool a_CancelPendingOperations = false) override final;
        virtual EFileResult Read(char* a_ReadBuffer, FSize a_BufferSize, FSize* a_BytesRead = nullptr) override final;
        virtual EFileResult Write(const char* a_WriteBuffer, FSize a_BufferSize) override final;
        virtual EFileResult Seek(const EFileSeekOrigin a_SeekOrigin, FSize a_SeekPos, FSize* a_NewPosition = nullptr) override final;
        virtual EFileResult GetLength(FSize& a_FileLength) override final;

    private:
        OpenFlagType ConvertOpenFlags(const EFileOpenFlags a_OpenFlags) const;
        SeekOriginType ConvertSeekOrigin(const EFileSeekOrigin a_SeekOrigin) const;

    private:
        FileType* m_FileHandle;
        FSize m_FileLength;
    };
}