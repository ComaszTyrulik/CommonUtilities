#pragma once
#include "Common/Filesystem/Types.h"
#include "Common/Helpers.h"

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief General interface providing basic functionalities of the filesystem, such as reading and creating files.
     * It's meant to be used as the abstract and easy way to operate on the underlying OS's filesystem.
     */
    class IFilesystem
    {
    public:
        CT_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(IFilesystem);
        IFilesystem() = default;
        virtual ~IFilesystem() = default;

        /**
         * @brief Returns information whether passed directory exists.
         * Returns true if directory exists and is a directory. Returns false otherwise.
         * 
         * @param directoryPath
         * @return 
         */
        [[nodiscard]] virtual bool DirectoryExists(const FilesystemPath& directoryPath) const = 0;

        /**
         * @brief Creates directory under given directoryPath.
         * Throws exception if directory already exists or cannot be created.
         * 
         * @param directoryPath
         */
        virtual void CreateDirectory(const FilesystemPath& directoryPath) const = 0;

        /**
         * @brief Returns information whether passed file exists.
         * Returns true if file exists and is a regular file. Returns false otherwise.
         * 
         * @param filePath
         * @return 
         */
        [[nodiscard]] virtual bool FileExists(const FilesystemPath& filePath) const = 0;

        /**
         * @brief Creates file under given filePath.
         * If fileContent is provided, it is saved as the new file's content. Otherwise, an empty file is created.
         * Throws exception if file already exists or cannot be created.
         * 
         * @param filePath
         * @param fileContent
         */
        virtual void CreateFile(const FilesystemPath& filePath, std::string_view fileContent = "") const = 0;

        /**
         * @brief Updates file under given filePath containing passed fileContent.
         * Throws exception if file does not exist or cannot be updated.
         * 
         * @param filePath
         * @param fileContent
         */
        virtual void UpdateFile(const FilesystemPath& filePath, std::string_view fileContent) const = 0;

        /**
         * @brief Removes file under given filePath from filesystem.
         * Throws exception if file does not exist or cannot be deleted.
         * 
         * @param filePath
         */
        virtual void DeleteFile(const FilesystemPath& filePath) const = 0;

        /**
         * @brief Reads content of the file under given filePath and returns it as string.
         * Throws exception if file does not exist or cannot be opened.
         * 
         * @param filePath
         * @return 
         */
        [[nodiscard]] virtual std::string ReadFile(const FilesystemPath& filePath) const = 0;

        /**
         * @brief Reads contents of every file inside the given directoryPath.
         * Interprets each file as a text file, meaning each file's content is read as text.
         * Returns read files as an array where each index corresponds to a single file content.
         * If directory contains subdirectories, they are omitted.
         * This means that this method reads files only from the given directory.
         * If directory is empty, empty array is returned.
         * Throws exception if given directory does not exist.
         * 
         * @param directoryPath
         * @return 
         */
        [[nodiscard]] virtual std::vector<std::string> ReadAllFilesInDirectory(const FilesystemPath& directoryPath) const = 0;
    };
} // namespace CT_COMMON_NAMESPACE
