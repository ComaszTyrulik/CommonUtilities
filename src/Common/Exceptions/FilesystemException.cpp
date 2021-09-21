#pragma once
#include "Common/Exceptions/FilesystemException.h"

#include <fmt/format.h>

namespace CT_COMMON_NAMESPACE
{
    std::runtime_error FilesystemExceptionsGenerator::DirectoryExists(const FilesystemPath& directoryPath)
    {
        const auto message = fmt::format("'{}' directory already exists!", directoryPath.u8string());
        return std::runtime_error(message);
    }

    std::runtime_error FilesystemExceptionsGenerator::DirectoryNotExists(const FilesystemPath& directoryPath)
    {
        const auto message = fmt::format("'{}' directory does not exist!", directoryPath.u8string());
        return std::runtime_error(message);
    }

    std::runtime_error FilesystemExceptionsGenerator::FileExists(const FilesystemPath& filePath)
    {
        const auto message = fmt::format("'{}' file already exists!", filePath.u8string());
        return std::runtime_error(message);
    }

    std::runtime_error FilesystemExceptionsGenerator::FileNotExists(const FilesystemPath& filePath)
    {
        const auto message = fmt::format("'{}' file does not exist!", filePath.u8string());
        return std::runtime_error(message);
    }

    std::runtime_error FilesystemExceptionsGenerator::FileNotOpened(const FilesystemPath& filePath)
    {
        const auto message = fmt::format("'{}' file could not be opened!", filePath.u8string());
        return std::runtime_error(message);
    }
} // namespace CT_COMMON_NAMESPACE
