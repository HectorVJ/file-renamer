#ifndef RENAME_EXECUTOR_H
#define RENAME_EXECUTOR_H

#include "file_entry.h"
#include <vector>
#include <string>
#include <utility>

struct RenameResult {
    std::string oldPath;
    std::string newPath;
    bool success;
    std::string errorMessage;
};

class RenameExecutor {
public:
    std::vector<RenameResult> execute(const std::vector<std::pair<FileEntry, std::string>>& renamePairs);
    std::vector<RenameResult> preview(const std::vector<std::pair<FileEntry, std::string>>& renamePairs);
    int detectConflicts(const std::vector<std::pair<FileEntry, std::string>>& renamePairs) const;
};

#endif