#ifndef FILE_SCANNER_H
#define FILE_SCANNER_H

#include "file_entry.h"
#include <vector>
#include <string>

class FileScanner {
public:
    explicit FileScanner(const std::string& directory);
    bool scan(std::vector<FileEntry>& files);
    const std::string& getLastError() const { return lastError_; }
private:
    std::string directory_;
    std::string lastError_;
};

#endif