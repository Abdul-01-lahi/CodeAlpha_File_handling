#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

void listFilesInDirectory(const fs::path& directoryPath) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        std::cout << entry.path().filename() << "\n";
    }
}

void createDirectory(const fs::path& parentPath, const std::string& dirName) {
    fs::create_directory(parentPath / dirName);
}

void copyFile(const fs::path& sourcePath, const fs::path& destinationPath) {
    fs::copy_file(sourcePath, destinationPath, fs::copy_options::overwrite_existing);
}

void moveFile(const fs::path& sourcePath, const fs::path& destinationPath) {
    fs::rename(sourcePath, destinationPath);
}

int main() {
    fs::path currentDirectory = fs::current_path();

    while (true) {
        std::cout << "Current Directory: " << currentDirectory << "\n";
        std::cout << "Commands: 'ls' (list), 'cd <dir>' (change directory), 'mkdir <dir>' (create directory), 'cp <file> <destination>' (copy file), 'mv <file> <destination>' (move file), 'exit'\n";
        std::cout << "Enter command: ";

        std::string command;
        std::getline(std::cin, command);

        std::vector<std::string> tokens;
        std::istringstream tokenStream(command);
        std::string token;
        while (std::getline(tokenStream, token, ' ')) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }

        if (tokens[0] == "ls") {
            listFilesInDirectory(currentDirectory);
        } else if (tokens[0] == "cd" && tokens.size() == 2) {
            fs::path newDir = currentDirectory / tokens[1];
            if (fs::is_directory(newDir)) {
                currentDirectory = newDir;
            } else {
                std::cout << "Directory not found.\n";
            }
        } else if (tokens[0] == "mkdir" && tokens.size() == 2) {
            createDirectory(currentDirectory, tokens[1]);
        } else if (tokens[0] == "cp" && tokens.size() == 3) {
            copyFile(currentDirectory / tokens[1], currentDirectory / tokens[2]);
        } else if (tokens[0] == "mv" && tokens.size() == 3) {
            moveFile(currentDirectory / tokens[1], currentDirectory / tokens[2]);
        } else if (tokens[0] == "exit") {
            break;
        } else {
            std::cout << "Invalid command.\n";
        }
    }

    return 0;
}
