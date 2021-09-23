#include "FilesystemTest.h"

#include <Common/Filesystem/Filesystem.h>

namespace CT_COMMON_NAMESPACE::tests::integration
{
    TEST_F(FilesystemTest, DoesDirectoryExistWillReturnTrueIfGivenPathExistsAndIsDirectory)
    {
        const std::string directoryName = "ExistingDirectory";
        const auto directoryPath = CreateDirectory(directoryName);

        const Filesystem sut;
        ASSERT_TRUE(sut.DirectoryExists(directoryPath));
    }

    TEST_F(FilesystemTest, DoesDirectoryExistWillReturnFalseIfGivenDirectoryDoesNotExist)
    {
        const std::string directoryName = "NonExistingDirectory";
        const auto directoryPath = GetFullPath(directoryName);

        const Filesystem sut;
        ASSERT_FALSE(sut.DirectoryExists(directoryPath));
    }

    TEST_F(FilesystemTest, DoesDirectoryExistWillReturnFalseIfGivenPathExistsButIsNotDirectory)
    {
        const std::string invalidDirectoryName = "FileNotDir.txt";
        const auto invalidDirectoryPath = CreateFile(invalidDirectoryName);

        const Filesystem sut;
        ASSERT_FALSE(sut.DirectoryExists(invalidDirectoryPath));
    }

    TEST_F(FilesystemTest, CreateDirectoryWillCreateSingleDirectoryIfGivenPathIsValidAndDirectoryDoesNotExist)
    {
        const std::string directoryName = "ValidDirectory";
        const auto directoryPath = GetFullPath(directoryName);

        const bool directoryExistanceBefore = fs::exists(directoryPath);

        const Filesystem sut;
        sut.CreateDirectory(directoryPath);

        const bool directoryExistanceAfter = fs::exists(directoryPath);
        ASSERT_FALSE(directoryExistanceBefore);
        ASSERT_TRUE(directoryExistanceAfter);
    }

    TEST_F(FilesystemTest, CreateDirectoryWillThrowExceptionIfDirectoryAlreadyExists)
    {
        const std::string directoryName = "ValidDirectory";
        const auto directoryPath = CreateDirectory(directoryName);

        const Filesystem sut;
        ASSERT_THROW(sut.CreateDirectory(directoryPath), std::runtime_error);
    }

    TEST_F(FilesystemTest, CreateDirectoryWillThrowExceptionIfGivenPathConsistsOfNonExistentDirectories)
    {
        const auto invalidDirectoryPath = GetFullPath("NonExistent1/NonExistent2/Dir");

        const Filesystem sut;
        ASSERT_THROW(sut.CreateDirectory(invalidDirectoryPath), std::runtime_error);
    }

    TEST_F(FilesystemTest, CreateDirectoryWillThrowExceptionIfFileWithGivenNameExistsUnderGivenPath)
    {
        const std::string invalidDirectoryName = "FileNotDir.txt";
        const auto invalidDirectoryPath = CreateFile(invalidDirectoryName);

        const Filesystem sut;
        ASSERT_THROW(sut.CreateDirectory(invalidDirectoryPath), std::runtime_error);
    }

    TEST_F(FilesystemTest, DoesFileExistWillReturnTrueIfGivenPathExistsAndIsFile)
    {
        const std::string filename = "File.txt";
        const auto filePath = CreateFile(filename);

        const Filesystem sut;
        ASSERT_TRUE(sut.FileExists(filePath));
    }

    TEST_F(FilesystemTest, DoesFileExistWillReturnFalseIfGivenFileDoesNotExists)
    {
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);

        const Filesystem sut;
        ASSERT_FALSE(sut.FileExists(filePath));
    }

    TEST_F(FilesystemTest, DoesFileExistWillReturnFalseIfGivenPathExistsButIsNotFile)
    {
        const std::string invalidFilename = "ThisIsDirectory!";
        const auto invalidFilePath = CreateDirectory(invalidFilename);

        const Filesystem sut;
        ASSERT_FALSE(sut.FileExists(invalidFilePath));
    }

    TEST_F(FilesystemTest, CreateFileWillCreateGivenFileIfGivenPathDoesNotExistAndIsValidPath)
    {
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);
        
        const bool fileExistanceBefore = fs::exists(filePath);

        const Filesystem sut;
        sut.CreateFile(filePath);
        
        const bool fileExistanceAfter = fs::exists(filePath);
        ASSERT_FALSE(fileExistanceBefore);
        ASSERT_TRUE(fileExistanceAfter);
    }

    TEST_F(FilesystemTest, CreateFileWillThrowExceptionIfFileAlreadyExists)
    {
        const std::string filename = "File.txt";
        const auto filePath = CreateFile(filename);

        const Filesystem sut;
        ASSERT_THROW(sut.CreateFile(filePath), std::runtime_error);
    }

    TEST_F(FilesystemTest, CreateFileWillThrowExceptionIfGivenFilePathContainsNonExistentDirectories)
    {
        const std::string filename = "Non/Existent/PathTo/File.txt";
        const auto filePath = GetFullPath(filename);

        const Filesystem sut;
        ASSERT_THROW(sut.CreateFile(filePath), std::runtime_error);
    }

    TEST_F(FilesystemTest, CreateFileWillCreateFileWithGivenContent)
    {
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);
        
        const std::string expectedFileContent = "This is a file content";

        const Filesystem sut;
        sut.CreateFile(filePath, expectedFileContent);

        const auto actualFileContent = ReadFile(filePath);
        ASSERT_EQ(expectedFileContent, actualFileContent);
    }

    TEST_F(FilesystemTest, UpdateFileWillThrowExceptionIfGivenFileDoesNotExist)
    {
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);

        const Filesystem sut;
        ASSERT_THROW(sut.UpdateFile(filePath, "New content"), std::runtime_error);
    }

    TEST_F(FilesystemTest, UpdateFileWillUpdateFileContentWithGivenNewContent)
    {
        const std::string expectedContent = "This is my content\nWith new line";
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);

        CreateFile(filename, "file content before");
        const auto contentBefore = ReadFile(filePath);

        const Filesystem sut;
        sut.UpdateFile(filePath, expectedContent);

        const auto actualContent = ReadFile(filePath);
        ASSERT_NE(expectedContent, contentBefore);
        ASSERT_EQ(expectedContent, actualContent);
    }

    TEST_F(FilesystemTest, ReadFileWillThrowExceptionIfGivenFileDoesNotExist)
    {
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);

        const Filesystem sut;
        ASSERT_THROW(sut.ReadFile(filePath), std::runtime_error);
    }

    TEST_F(FilesystemTest, ReadFileWillReturnGivenFileContent)
    {
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);

        const std::string expectedContent = "This is my content\nWith new line";
        CreateFile(filename, expectedContent);

        const Filesystem sut;
        const auto actualContent = sut.ReadFile(filePath);
        ASSERT_EQ(expectedContent, actualContent);
    }

    TEST_F(FilesystemTest, DeleteFileWillThrowExceptionIfGivenFileDoesNotExist)
    {
        const std::string filename = "File.txt";
        const auto filePath = GetFullPath(filename);

        const Filesystem sut;
        ASSERT_THROW(sut.DeleteFile(filePath), std::runtime_error);
    }

    TEST_F(FilesystemTest, DeleteFileWillRemoveFileFromDisk)
    {
        const std::string filename = "File.txt";
        const auto filePath = CreateFile(filename);

        const bool fileExistanceBefore = fs::exists(filePath);

        const Filesystem sut;
        sut.DeleteFile(filePath);

        const bool fileExistanceAfter = fs::exists(filePath);
        ASSERT_NE(fileExistanceBefore, fileExistanceAfter);
        ASSERT_FALSE(fileExistanceAfter);
    }

    TEST_F(FilesystemTest, ReadAllFilesInDirectoryWillReturnEmptyArrayIfGivenDirectoryIsEmpty)
    {
        const std::string emptyDirectoryName = "EmptyDir";
        const auto emptyDirectoryPath = CreateDirectory(emptyDirectoryName);

        const Filesystem sut;
        const auto actualFiles = sut.ReadAllFilesInDirectory(emptyDirectoryPath);
        ASSERT_TRUE(actualFiles.empty());
    }

    TEST_F(FilesystemTest, ReadAllFilesInDirectoryWillThrowExceptionIfGivenDirectoryDoesNotExist)
    {
        const std::string nonexistentDirectoryPath = "Nonexistent";

        const Filesystem sut;
        ASSERT_THROW(sut.ReadAllFilesInDirectory(nonexistentDirectoryPath), std::runtime_error);
    }

    TEST_F(FilesystemTest, ReadAllFilesInDirectoryWillThrowExceptionIfGivenDirectoryPathIsFile)
    {
        const auto invalidDirectoryPath = CreateFile("FileNotDir.txt");

        const Filesystem sut;
        ASSERT_THROW(sut.ReadAllFilesInDirectory(invalidDirectoryPath), std::runtime_error);
    }

    TEST_F(FilesystemTest, ReadAllFilesInDirectoryWillReadSingleFileFromGivenDirectory)
    {
        const FilesystemPath directoryName = "Directory";
        const auto directoryPath = CreateDirectory(directoryName);
        
        const std::size_t expectedFilesArrayCount = 1;
        const auto expectedFileContent = "FileContent";
        const auto filePath = directoryName / "Filename.txt";

        CreateFile(filePath, expectedFileContent);

        const Filesystem sut;
        const auto actualFiles = sut.ReadAllFilesInDirectory(directoryPath);

        ASSERT_EQ(expectedFilesArrayCount, actualFiles.size());
        ASSERT_EQ(expectedFileContent, actualFiles[0]);
    }

    TEST_F(FilesystemTest, ReadAllFilesInDirectoryWillReadAllFilesFromGivenDirectory)
    {
        const FilesystemPath directoryName = "Directory";
        const auto directoryPath = CreateDirectory(directoryName);

        const std::size_t expectedFilesArrayCount = 100;
        auto expectedFiles = CreateMultipleFilesInDirectory(expectedFilesArrayCount, directoryName);

        const Filesystem sut;
        auto actualFiles = sut.ReadAllFilesInDirectory(directoryPath);

        std::sort(expectedFiles.begin(), expectedFiles.end());
        std::sort(actualFiles.begin(), actualFiles.end());

        ASSERT_EQ(expectedFilesArrayCount, actualFiles.size());
        ASSERT_TRUE(std::includes(expectedFiles.begin(), expectedFiles.end(), actualFiles.begin(), actualFiles.end()));
    }

    TEST_F(FilesystemTest, ReadAllFilesInDirectoryWillOmitSubdirectories)
    {
        const FilesystemPath directoryName = "Directory";
        const auto directoryPath = CreateDirectory(directoryName);

        const FilesystemPath subDirectoryName = directoryName / "Subdir";
        CreateDirectory(subDirectoryName);
        CreateFile(subDirectoryName / "FileInSubDir.txt");

        const std::size_t expectedFilesArrayCount = 1;
        const auto expectedFileContent = "FileContent";
        const auto filePath = directoryName / "Filename.txt";

        CreateFile(filePath, expectedFileContent);

        const Filesystem sut;
        const auto actualFiles = sut.ReadAllFilesInDirectory(directoryPath);

        ASSERT_EQ(expectedFilesArrayCount, actualFiles.size());
        ASSERT_EQ(expectedFileContent, actualFiles[0]);
    }
} // namespace sce::tests::integration
