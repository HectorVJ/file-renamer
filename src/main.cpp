#include "cli.h"
#include "file_scanner.h"
#include "file_filter.h"
#include "rename_rule.h"
#include <iostream>
#include <utility>

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
    if (files.empty()) {
        std::cout << "No files found in directory." << std::endl;
        return 0;
    }

    FileFilter filter;
    filter.setExtensionFilter(options.extensionFilter);
    std::vector<FileEntry> filteredFiles = filter.apply(files);
    
    std::cout << "Files after filter: " << filteredFiles.size() << std::endl;
    if (filteredFiles.empty()) {
        std::cout << "No files match the filter criteria." << std::endl;
        return 0;
    }

    RenameRule rule;
    rule.setPrefix(options.prefix);
    rule.setSuffix(options.suffix);
    rule.setReplaceFrom(options.replaceFrom);
    rule.setReplaceTo(options.replaceTo);
    rule.setNumbering(options.enableNumbering, options.startNumber, options.numberWidth);

    std::cout << "\nRename preview:" << std::endl;
    for (size_t i = 0; i < filteredFiles.size(); ++i) {
        std::string newName = rule.apply(filteredFiles[i].filename, filteredFiles[i].extension, i);
        std::cout << "  " << filteredFiles[i].filename << " -> " << newName << std::endl;
    }

    return 0;
}