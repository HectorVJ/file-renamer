#include "rename_executor.h"
#include <filesystem>
#include <iostream>
#include <unordered_map>

namespace fs = std::filesystem;

int RenameExecutor::detectConflicts(const std::vector<std::pair<FileEntry, std::string>>& renamePairs) const {
    int conflictCount = 0;
    std::unordered_map<std::string, int> targetCounts;

    for (const auto& pair : renamePairs) {
        const fs::path sourcePath(pair.first.path);
        const fs::path targetPath = sourcePath.parent_path() / pair.second;
        const std::string targetKey = targetPath.lexically_normal().string();

        targetCounts[targetKey]++;
        if (targetCounts[targetKey] > 1) {
            conflictCount++;
        }

        if (targetPath == sourcePath) {
            continue;
        }

        if (fs::exists(targetPath)) {
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

        const fs::path sourcePath(pair.first.path);
        const fs::path targetPath = sourcePath.parent_path() / pair.second;

        if (targetPath == sourcePath) {
            result.success = true;
            std::cout << "Skipped: " << pair.first.filename << " (name unchanged)" << std::endl;
            results.push_back(result);
            continue;
        }

        try {
            fs::rename(sourcePath, targetPath);
            result.success = true;
            std::cout << "Renamed: " << pair.first.filename << " -> " << pair.second << std::endl;
        } catch (const fs::filesystem_error& ex) {
            result.success = false;
            result.errorMessage = ex.what();
            std::cerr << "Failed: " << pair.first.filename << " - " << ex.what() << std::endl;
        }
        
        results.push_back(result);
    }
    
    return results;
}
