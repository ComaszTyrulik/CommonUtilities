#include "Common/Filesystem/Filesystem.h"
#include "Common/Exceptions/FilesystemException.h"
#include "Common/Types.h"
#include "Common/Exceptions.h"
#include "Common/Utils/ThreadUtils/AsyncTaskExecutor.h"

#include <fmt/format.h>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <future>

namespace CT_COMMON_NAMESPACE
{
    namespace fs = std::filesystem;

    bool Filesystem::DirectoryExists(const FilesystemPath& directoryPath) const
    {
        return fs::exists(directoryPath) ? fs::is_directory(directoryPath) : false;
    }

    void Filesystem::CreateDirectory(const FilesystemPath& directoryPath) const
    {
        if (DirectoryExists(directoryPath))
        {
            CT_THROW_FROM(FilesystemExceptionsGenerator::DirectoryExists(directoryPath));
        }

        fs::create_directory(directoryPath);
    }

    bool Filesystem::FileExists(const FilesystemPath& filePath) const
    {
        return fs::exists(filePath) ? fs::is_regular_file(filePath) : false;
    }

    void Filesystem::CreateFile(const FilesystemPath& filePath, std::string_view fileContent) const
    {
        if (FileExists(filePath))
        {
            CT_THROW_FROM(FilesystemExceptionsGenerator::FileExists(filePath));
        }

        SaveContentToFile(filePath, fileContent);
    }

    void Filesystem::UpdateFile(const FilesystemPath& filePath, std::string_view fileContent) const
    {
        if (!FileExists(filePath))
        {
            CT_THROW_FROM(FilesystemExceptionsGenerator::FileNotExists(filePath));
        }

        SaveContentToFile(filePath, fileContent);
    }

    void Filesystem::DeleteFile(const FilesystemPath& filePath) const
    {
        if (!FileExists(filePath))
        {
            CT_THROW_FROM(FilesystemExceptionsGenerator::FileNotExists(filePath));
        }

        fs::remove(filePath);
    }

    std::string Filesystem::ReadFile(const FilesystemPath& filePath) const
    {
        if (!FileExists(filePath))
        {
            CT_THROW_FROM(FilesystemExceptionsGenerator::FileNotExists(filePath));
        }

        return ReadFileContent(filePath);
    }

    std::vector<std::string> Filesystem::ReadAllFilesInDirectory(const FilesystemPath& directoryPath) const
    {
        if (!DirectoryExists(directoryPath))
        {
            CT_THROW_FROM(FilesystemExceptionsGenerator::DirectoryNotExists(directoryPath));
        }

        std::vector<std::string> filesContents;
        const auto filesToRead = GetAllFilesFromDirectory(directoryPath);        
        ReadFilesContents(filesToRead, filesContents);

        return filesContents;
    }

    void Filesystem::SaveContentToFile(const FilesystemPath& filePath, std::string_view fileContent) const
    {
        std::ofstream file(filePath);
        if (!file.is_open())
        {
            CT_THROW_FROM(FilesystemExceptionsGenerator::FileNotOpened(filePath));
        }

        file << fileContent;
        file.close();
    }
    
    std::string Filesystem::ReadFileContent(const FilesystemPath& filePath) const
    {
        std::stringstream buffer;
        std::ifstream file(filePath);
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }
    
    std::vector<FilesystemPath> Filesystem::GetAllFilesFromDirectory(const FilesystemPath& directoryPath) const
    {
        std::vector<FilesystemPath> filesToRead;
        filesToRead.reserve(fs::file_size(directoryPath));
        for (const auto& entry : fs::directory_iterator(directoryPath))
        {
            if (fs::is_regular_file(entry))
            {
                filesToRead.push_back(entry.path());
            }
        }

        return filesToRead;
    }
    
    void Filesystem::ReadFilesContents(const std::vector<FilesystemPath>& filesToRead, std::vector<std::string>& filesContents) const
    {
        if (filesToRead.empty())
        {
            return;
        }

        const auto numberOfFiles = filesToRead.size();
        filesContents.resize(numberOfFiles);
        
        AsyncTaskExecutor(numberOfFiles, [&](std::size_t firstIndex, std::size_t lastIndex) {
            for (std::size_t index = firstIndex; index <= lastIndex; ++index)
            {
                filesContents[index] = ReadFileContent(filesToRead[index]);
            }
        }).Execute();
    }
} // namespace sce::brain
