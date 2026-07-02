#include "file_filter.h"
#include <algorithm>
#include <cctype>

void FileFilter::setExtensionFilter(const std::string& ext) {
    extensionFilter_ = ext;
}

void FileFilter::setKeywordFilter(const std::string& keyword) {
    keywordFilter_ = keyword;
}

std::vector<FileEntry> FileFilter::apply(const std::vector<FileEntry>& files) const {
    std::vector<FileEntry> result;
    
    for (const auto& file : files) {
        bool matchesExt = extensionFilter_.empty() || 
            file.extension == extensionFilter_;
        bool matchesKeyword = keywordFilter_.empty() ||
            file.filename.find(keywordFilter_) != std::string::npos;
        
        if (matchesExt && matchesKeyword) {
            result.push_back(file);
        }
    }
    
    return result;
}