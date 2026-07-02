#include "cli.h"
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

    std::cout << "Input directory: " << options.inputDir << std::endl;
    std::cout << "Mode: " << (options.previewMode ? "preview" : "execute") << std::endl;
    if (!options.extensionFilter.empty()) {
        std::cout << "Extension filter: " << options.extensionFilter << std::endl;
    }

    return 0;
}