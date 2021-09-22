#pragma once
#include "Common/Resources.h"

#include <filesystem>

namespace CT_COMMON_NAMESPACE
{
    using FilesystemPath = std::filesystem::path;

    inline FilesystemPath operator+(const FilesystemPath& path1, const char* path2)
    {
        return FilesystemPath(path1.u8string() + path2);
    }

    inline FilesystemPath operator+(const FilesystemPath& path1, const std::string& path2)
    {
        return FilesystemPath(path1.u8string() + path2);
    }

    inline FilesystemPath operator+(const FilesystemPath& path1, const FilesystemPath& path2)
    {
        return FilesystemPath(path1.u8string() + path2.u8string());
    }
} // namespace CT_COMMON_NAMESPACE
