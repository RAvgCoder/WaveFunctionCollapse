//
// Created by egbor on 2024-01-02.
//

#include <fstream>
#include <iostream>

/**
 * \brief Opens the file, reads the first byte in hexadecimal format, and returns the file stream.
 * \param relative_file_path Relative path from the base directory [WaveFunctionCollapse/..].
 * \return An std::ifstream object representing the opened file stream.
 */
std::ifstream openFile(const std::string& relative_file_path) {
    std::ifstream file(relative_file_path, std::ios::binary); // Path relative to the base directory

    if (file.is_open()) {
        // Get the file size
        file.seekg(0, std::ios::end); // Move to the end of the file
        std::streampos fileSize = file.tellg(); // Get the current position, which is the file size
        file.seekg(0, std::ios::beg); // Move back to the beginning of the file

        char firstByte = '\0'; // Initialize with null character

        // Read the first byte as a char
        file.read(&firstByte, sizeof(char));

        std::cout << "File size: " << fileSize << " bytes" << std::endl;
        printf("First byte in hexadecimal: 0x%x\n", firstByte);

        // Return the file stream
        return file;
    } else {
        std::cout << "Unable to open the file." << std::endl;
        // Return an empty file stream in case of failure
        return {};
    }
}



#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <string>

/**
 * \brief: Gets the absolute file path to the file
 * \param filePath The file Path to the file
 * \return The absolute file path
 */
std::string getAbsolutePath(const char* filePath) {
    std::string absolutePath;
#ifdef _WIN32
    char fullPath[MAX_PATH];
    DWORD length = GetFullPathNameA(filePath, MAX_PATH, fullPath, nullptr);
    if (length != 0) {
        absolutePath = fullPath;
    }
#else
    char resolvedPath[PATH_MAX];
    if (realpath(filePath, resolvedPath) != nullptr) {
        absolutePath = resolvedPath;
    }
#endif
    return absolutePath;
}
