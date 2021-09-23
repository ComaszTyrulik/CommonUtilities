#pragma once
#include "Common/Filesystem/IFilesystem.h"
#include "Common/Filesystem/Types.h"

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Basic IFilesystem implementation using std::filesystem.
     */
    class Filesystem final : public IFilesystem
    {
    public:
        bool DirectoryExists(const FilesystemPath& directoryPath) const override;
        void CreateDirectory(const FilesystemPath& directoryPath) const override;
        bool FileExists(const FilesystemPath& filePath) const override;
        void CreateFile(const FilesystemPath& filePath, std::string_view fileContent = "") const override;
        void UpdateFile(const FilesystemPath& filePath, std::string_view fileContent) const override;
        void DeleteFile(const FilesystemPath& filePath) const override;
        std::string ReadFile(const FilesystemPath& filePath) const override;
        std::vector<std::string> ReadAllFilesInDirectory(const FilesystemPath& directoryPath) const override;

    private:
        /**
         * @brief Opens file under given filePath and updates its contents to fileContent.
         * Throws exception on failure
         * 
         * @param filePath
         * @param fileContent
         */
        void SaveContentToFile(const FilesystemPath& filePath, std::string_view fileContent) const;

        /**
         * @brief Opens file under given filePath, reads and returns its content.
         * 
         * @param filePath
         */
        std::string ReadFileContent(const FilesystemPath& filePath) const;

        /**
         * @brief Returns a list of files from given directoryPath.
         * This list contains only the actual files.
         * 
         * @param directoryPath
         * @return 
         */
        std::vector<FilesystemPath> GetAllFilesFromDirectory(const FilesystemPath& directoryPath) const;

        /**
         * @brief Reads all files from filesToRead into the filesContents in an asynchronous way.
         * 
         * @param filesToRead
         * @param filesContents
         */
        void ReadFilesContents(const std::vector<FilesystemPath>& filesToRead, std::vector<std::string>& filesContents) const;
    };
} // namespace CT_COMMON_NAMESPACE
