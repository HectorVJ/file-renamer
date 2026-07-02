#include "file_scanner.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

FileScanner::FileScanner(const std::string& directory) : directory_(directory) {}

bool FileScanner::scan(std::vector<FileEntry>& files) {
    files.clear();
    
    if (!fs::exists(directory_)) {
        lastError_ = "Directory does not exist: " + directory_;
        return false;
    }
    
    if (!fs::is_directory(directory_)) {
        lastError_ = "Path is not a directory: " + directory_;
        return false;
    }
    
    try {
        for (const auto& entry : fs::directory_iterator(directory_)) {
            if (entry.is_regular_file()) {
                FileEntry fe;
                fe.path = entry.path().string();
                fe.filename = entry.path().stem().string();
                fe.extension = entry.path().extension().string();
                if (!fe.extension.empty() && fe.extension[0] == '.') {
                    fe.extension = fe.extension.substr(1);
                }
                files.push_back(fe);
            }
        }
    } catch (const fs::filesystem_error& ex) {
        lastError_ = "Failed to scan directory: " + std::string(ex.what());
        return false;
    }
    
    return true;
}