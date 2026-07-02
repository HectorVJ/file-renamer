#include "cli.h"
#include "file_scanner.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printUsage(argv[0]);
        return 0;
    }

    CliOptions options;
    if (!parseArguments(argc, argv, options)) {
        printUsage(argv[0]);
        return 1;
    }

    if (!validateOptions(options)) {
        return 1;
    }

    FileScanner scanner(options.inputDir);
    std::vector<FileEntry> files;
    
    if (!scanner.scan(files)) {
        std::cerr << "Error: " << scanner.getLastError() << std::endl;
        return 1;
    }

    std::cout << "Scan completed. Total files found: " << files.size() << std::endl;

    return 0;
}