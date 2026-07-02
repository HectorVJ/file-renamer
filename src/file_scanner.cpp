#include "file_scanner.h"
#include <iostream>
#include <windows.h>

namespace {
std::string joinPath(const std::string& base, const std::string& name) {
    if (base.empty()) {
        return name;
    }
    const char last = base.back();
    if (last == '\\' || last == '/') {
        return base + name;
    }
    return base + "\\" + name;
}

std::string stripExtension(const std::string& filename) {
    const std::size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos || pos == 0) {
        return filename;
    }
    return filename.substr(0, pos);
}

std::string getExtension(const std::string& filename) {
    const std::size_t pos = filename.find_last_of('.');
    if (pos == std::string::npos || pos == filename.size() - 1) {
        return "";
    }
    return filename.substr(pos + 1);
}
}

FileScanner::FileScanner(const std::string& directory) : directory_(directory) {}

bool FileScanner::scan(std::vector<FileEntry>& files) {
    files.clear();

    const DWORD attributes = GetFileAttributesA(directory_.c_str());
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        lastError_ = "Directory does not exist: " + directory_;
        return false;
    }

    if ((attributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
        lastError_ = "Path is not a directory: " + directory_;
        return false;
    }

    WIN32_FIND_DATAA findData;
    const std::string pattern = joinPath(directory_, "*");
    HANDLE findHandle = FindFirstFileA(pattern.c_str(), &findData);
    if (findHandle == INVALID_HANDLE_VALUE) {
        lastError_ = "Failed to scan directory: " + directory_;
        return false;
    }

    do {
        const std::string name = findData.cFileName;
        if (name == "." || name == "..") {
            continue;
        }

        if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
            continue;
        }

        FileEntry fe;
        fe.path = joinPath(directory_, name);
        fe.filename = stripExtension(name);
        fe.extension = getExtension(name);
        files.push_back(fe);
    } while (FindNextFileA(findHandle, &findData) != 0);

    FindClose(findHandle);
    return true;
}
