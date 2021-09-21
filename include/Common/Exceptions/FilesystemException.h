#pragma once
#include "Common/Filesystem/Types.h"
#include "Common/Helpers.h"

#include <stdexcept>

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Generator containing helper functions for creating filesystem related exceptions.
     */
    class FilesystemExceptionsGenerator final
    {
    public:
        CT_IMPLEMENT_CLASS_NOT_CONSTRUCTIBLE(FilesystemExceptionsGenerator);

        [[nodiscard]] static std::runtime_error DirectoryExists(const FilesystemPath& directoryPath);
        [[nodiscard]] static std::runtime_error DirectoryNotExists(const FilesystemPath& directoryPath);
        [[nodiscard]] static std::runtime_error FileExists(const FilesystemPath& filePath);
        [[nodiscard]] static std::runtime_error FileNotExists(const FilesystemPath& filePath);
        [[nodiscard]] static std::runtime_error FileNotOpened(const FilesystemPath& filePath);
    };
} // namespace CT_COMMON_NAMESPACE
