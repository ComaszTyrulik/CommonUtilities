#pragma once
#include "Common/Filesystem/Types.h"
#include "Common/Helpers.h"

namespace CT_COMMON_NAMESPACE
{
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
        virtual bool DirectoryExists(const FilesystemPath& directoryPath) const = 0;

        /**
         * @brief Creates directory under given directoryPath.
         * Throws exception if directory already exists or cannot be created.
         * 
         * @param directoryPath
         */
        virtual void CreateDirectory(const FilesystemPath& directoryPath) const = 0;

        /**
         * @brief Returns information whether passed file exists.
         * Returns true if file exists and is a file. Returns false otherwise.
         * 
         * @param filePath
         * @return 
         */
        virtual bool FileExists(const FilesystemPath& filePath) const = 0;

        /**
         * @brief Creates file under given filePath containing passed fileContent.
         * Throws exception if file already exists or cannot be created.
         * 
         * @param filePath
         * @param fileContent
         */
        virtual void CreateFile(const FilesystemPath& filePath, std::string_view fileContent) const = 0;

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
         * @brief Reads contents of the file under given filePath and returns it as string.
         * Throws exception if file does not exists or cannot be opened.
         * 
         * @param filePath
         * @return 
         */
        virtual std::string ReadFile(const FilesystemPath& filePath) const = 0;

        /**
         * @brief Reads contents of every file inside the given directoryPath.
         * Interprets each file as a text file, meaning each file's content is treated as text.
         * Returns read files as an array where each index corresponds to a single file contents.
         * If directory contains subdirectories, they are omitted.
         * This means that this method reads files only from the given directory.
         * If directory is empty, empty array is returned.
         * Throws exception if given directory does not exist.
         * 
         * @param directoryPath
         * @return 
         */
        virtual std::vector<std::string> ReadAllFilesInDirectory(const FilesystemPath& directoryPath) const = 0;
    };
} // namespace CT_COMMON_NAMESPACE
