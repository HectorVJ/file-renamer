#include "rename_executor.h"
#include <iostream>
#include <windows.h>
#include <unordered_map>

namespace {
std::string getParentPath(const std::string& path) {
    const std::size_t pos = path.find_last_of("\\/");
    if (pos == std::string::npos) {
        return "";
    }
    return path.substr(0, pos);
}

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

bool pathExists(const std::string& path) {
    return GetFileAttributesA(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}
}

int RenameExecutor::detectConflicts(const std::vector<std::pair<FileEntry, std::string>>& renamePairs) const {
    int conflictCount = 0;
    std::unordered_map<std::string, int> targetCounts;

    for (const auto& pair : renamePairs) {
        const std::string sourcePath = pair.first.path;
        const std::string targetPath = joinPath(getParentPath(sourcePath), pair.second);
        const std::string targetKey = targetPath;

        targetCounts[targetKey]++;
        if (targetCounts[targetKey] > 1) {
            conflictCount++;
        }

        if (targetPath == sourcePath) {
            continue;
        }

        if (pathExists(targetPath)) {
            conflictCount++;
        }
    }

    return conflictCount;
}

std::vector<RenameResult> RenameExecutor::preview(const std::vector<std::pair<FileEntry, std::string>>& renamePairs) {
    std::vector<RenameResult> results;
    for (const auto& pair : renamePairs) {
        RenameResult result;
        result.oldPath = pair.first.path;
        result.newPath = pair.second;
        result.success = true;
        results.push_back(result);
    }
    return results;
}

std::vector<RenameResult> RenameExecutor::execute(const std::vector<std::pair<FileEntry, std::string>>& renamePairs) {
    std::vector<RenameResult> results;
    
    for (const auto& pair : renamePairs) {
        RenameResult result;
        result.oldPath = pair.first.path;
        result.newPath = pair.second;

        const std::string sourcePath = pair.first.path;
        const std::string targetPath = joinPath(getParentPath(sourcePath), pair.second);

        if (targetPath == sourcePath) {
            result.success = true;
            std::cout << "Skipped: " << pair.first.filename << " (name unchanged)" << std::endl;
            results.push_back(result);
            continue;
        }

        if (MoveFileExA(sourcePath.c_str(), targetPath.c_str(), MOVEFILE_REPLACE_EXISTING)) {
            result.success = true;
            std::cout << "Renamed: " << pair.first.filename << " -> " << pair.second << std::endl;
        } else {
            result.success = false;
            result.errorMessage = "Win32 error code: " + std::to_string(GetLastError());
            std::cerr << "Failed: " << pair.first.filename << " - " << result.errorMessage << std::endl;
        }

        results.push_back(result);
    }

    return results;
}
