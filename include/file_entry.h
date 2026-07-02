#ifndef FILE_ENTRY_H
#define FILE_ENTRY_H

#include <string>

struct FileEntry {
    std::string path;
    std::string filename;
    std::string extension;
};

#endif