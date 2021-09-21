#pragma once
#include <Common/Filesystem/Types.h>
#include <Common/Types.h>

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>
#include <execution>

namespace CT_COMMON_NAMESPACE::tests::integration
{
    namespace fs = std::filesystem;

    class FilesystemTestCase : public testing::Test
    {
    public:
        FilesystemTestCase()
        {
            constexpr auto baseDirectoryName = "CtTemp/";
            m_baseDirPath = FilesystemPath(fs::temp_directory_path().u8string() + baseDirectoryName + GenerateRandomString());
        }

    protected:
        void SetUp() override
        {
            CreateBaseDirectory();
        }

        void TearDown() override
        {
            DeleteBaseDirectory();
        }

        FilesystemPath CreateDirectory(const std::string& relativePath) const
        {
            auto fullPath = GetFullPath(relativePath);
            fs::create_directory(fullPath);

            return fullPath;
        }

        FilesystemPath CreateDirectory(const FilesystemPath& relativePath) const
        {
            return CreateDirectory(relativePath.u8string());
        }

        FilesystemPath CreateDirectory(const char* relativePath) const
        {
            return CreateDirectory(std::string(relativePath));
        }

        FilesystemPath CreateFile(const std::string& relativePath, const std::string& fileContent = "") const
        {
            auto fullFilePath = GetFullPath(relativePath);
            std::ofstream file(fullFilePath);
            if (!fileContent.empty())
            {
                file << fileContent;
            }
            file.close();

            return fullFilePath;
        }

        FilesystemPath CreateFile(const FilesystemPath& relativePath, const std::string& fileContent = "") const
        {
            return CreateFile(relativePath.u8string(), fileContent);
        }

        FilesystemPath CreateFile(const char* relativePath, const std::string& fileContent = "") const
        {
            return CreateFile(std::string(relativePath), fileContent);
        }

        FilesystemPath GetFullPath(const std::string& relativePath) const
        {
            return GetBaseDirectoryPath() + "/" + relativePath;
        }

        FilesystemPath GetFullPath(const FilesystemPath& relativePath) const
        {
            return GetFullPath(relativePath.u8string());
        }

        FilesystemPath GetFullPath(const char* relativePath) const
        {
            return GetFullPath(std::string(relativePath));
        }

        std::string ReadFile(const FilesystemPath& filePath) const
        {
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                throw std::runtime_error("Could not open file");
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            file.close();

            return buffer.str();
        }

        FilesystemPath GetBaseDirectoryPath() const
        {
            return m_baseDirPath;
        }

        std::vector<std::string> CreateMultipleFilesInDirectory(std::size_t numberOfFiles, const FilesystemPath& directoryRelativePath)
        {
            std::random_device rd;
            std::mt19937 generator(rd());

            std::vector<std::string> filesContents(numberOfFiles);
            std::for_each(std::execution::par_unseq, filesContents.begin(), filesContents.end(), [&](std::string& content) {
                content = GenerateRandomString();
                CreateFile((directoryRelativePath / content).u8string(), content);
            });

            return filesContents;
        }

    private:
        void CreateBaseDirectory() const
        {
            fs::create_directories(GetBaseDirectoryPath());
        }

        void DeleteBaseDirectory() const
        {
            const auto baseDirPath = GetBaseDirectoryPath();
            if (fs::exists(baseDirPath))
            {
                fs::remove_all(baseDirPath);
            }
        }

        std::string GenerateRandomString() const
        {
            const auto stringLength = 10;
            std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

            std::random_device rd;
            std::mt19937 generator(rd());

            std::shuffle(str.begin(), str.end(), generator);

            return str.substr(0, stringLength);
        }

    private:
        FilesystemPath m_baseDirPath;
    };
} // namespace CT_COMMON_NAMESPACE::tests::integration
