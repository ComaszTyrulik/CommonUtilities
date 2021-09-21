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

    class FileExtensionFilter final
    {
    public:
        FileExtensionFilter(std::string_view filterName, std::string_view filterFileExtension)
            : m_filterName(std::move(filterName)), m_fileExtension(std::move(filterFileExtension))
        {
        }

        const std::string_view& Name() const
        {
            return m_filterName;
        }

        const std::string_view& Extension() const
        {
            return m_fileExtension;
        }

    private:
        std::string_view m_filterName;
        std::string_view m_fileExtension;
    };
} // namespace CT_COMMON_NAMESPACE
