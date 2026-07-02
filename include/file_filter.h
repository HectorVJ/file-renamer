#ifndef FILE_FILTER_H
#define FILE_FILTER_H

#include "file_entry.h"
#include <vector>
#include <string>

class FileFilter {
public:
    void setExtensionFilter(const std::string& ext);
    void setKeywordFilter(const std::string& keyword);
    std::vector<FileEntry> apply(const std::vector<FileEntry>& files) const;
private:
    std::string extensionFilter_;
    std::string keywordFilter_;
};

#endif