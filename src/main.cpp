#include <iostream>

void printHelp() {
    std::cout << "file-renamer - Batch file rename tool\n"
              << "Usage: file-renamer [options]\n"
              << "Options:\n"
              << "  --help          Show this help message\n"
              << "  --input <path>  Specify input directory\n"
              << "  --preview       Preview rename results without executing\n"
              << "  --execute       Execute actual rename operations\n"
              << "  --prefix <str>  Add prefix to filenames\n"
              << "  --suffix <str>  Add suffix to filenames\n"
              << "  --replace <old> Replace keyword in filenames\n"
              << "  --with <new>    New keyword for replacement\n"
              << "  --number        Enable sequential numbering\n"
              << "  --start <n>     Starting number for numbering\n"
              << "  --width <n>     Number width with zero-padding\n"
              << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printHelp();
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help") {
            printHelp();
            return 0;
        }
    }

    return 0;
}