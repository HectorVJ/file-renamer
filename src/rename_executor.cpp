#include "rename_executor.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int RenameExecutor::detectConflicts(const std::vector<std::pair<FileEntry, std::string>>& renamePairs) const {
    int conflictCount = 0;
    for (const auto& pair : renamePairs) {
        std::string fullNewPath = fs::path(pair.first.path).parent_path().string() + "/" + pair.second;
        if (fs::exists(fullNewPath)) {
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
        
        std::string fullNewPath = fs::path(pair.first.path).parent_path().string() + "/" + pair.second;
        
        try {
            fs::rename(pair.first.path, fullNewPath);
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