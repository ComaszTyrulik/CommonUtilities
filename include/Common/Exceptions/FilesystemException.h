#pragma once
#include "Common/Filesystem/Types.h"
#include "Common/Helpers.h"

#include <stdexcept>

namespace CT_COMMON_NAMESPACE
{
    class FilesystemExceptionsGenerator final
    {
    public:
        CT_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(FilesystemExceptionsGenerator);
        FilesystemExceptionsGenerator() = delete;
        ~FilesystemExceptionsGenerator() = delete;

        static std::runtime_error DirectoryExists(const FilesystemPath& directoryPath);
        static std::runtime_error DirectoryNotExists(const FilesystemPath& directoryPath);
        static std::runtime_error FileExists(const FilesystemPath& filePath);
        static std::runtime_error FileNotExists(const FilesystemPath& filePath);
        static std::runtime_error FileNotOpened(const FilesystemPath& filePath);
    };
} // namespace CT_COMMON_NAMESPACE
