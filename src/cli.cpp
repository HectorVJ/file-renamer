#include "cli.h"
#include <exception>
#include <iostream>
#include <string>

void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [options]\n"
              << "Options:\n"
              << "  --help          Show this help message\n"
              << "  --input <path>  Specify input directory (required)\n"
              << "  --preview       Preview rename results without executing\n"
              << "  --execute       Execute actual rename operations\n"
              << "  --ext <ext>     Filter by extension (e.g., txt)\n"
              << "  --keyword <str> Filter filenames by keyword\n"
              << "  --prefix <str>  Add prefix to filenames\n"
              << "  --suffix <str>  Add suffix to filenames\n"
              << "  --replace <old> Replace keyword in filenames\n"
              << "  --with <new>    New keyword for replacement\n"
              << "  --number        Enable sequential numbering\n"
              << "  --start <n>     Starting number (default: 1)\n"
              << "  --width <n>     Number width with zero-padding (default: 3)\n"
              << std::endl;
}

bool parseArguments(int argc, char* argv[], CliOptions& options) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help") {
            return false;
        }
        else if (arg == "--input" && i + 1 < argc) {
            options.inputDir = argv[++i];
        }
        else if (arg == "--preview") {
            options.previewMode = true;
        }
        else if (arg == "--execute") {
            options.executeMode = true;
        }
        else if (arg == "--ext" && i + 1 < argc) {
            options.extensionFilter = argv[++i];
        }
        else if (arg == "--keyword" && i + 1 < argc) {
            options.keywordFilter = argv[++i];
        }
        else if (arg == "--prefix" && i + 1 < argc) {
            options.prefix = argv[++i];
        }
        else if (arg == "--suffix" && i + 1 < argc) {
            options.suffix = argv[++i];
        }
        else if (arg == "--replace" && i + 1 < argc) {
            options.replaceFrom = argv[++i];
        }
        else if (arg == "--with" && i + 1 < argc) {
            options.replaceTo = argv[++i];
        }
        else if (arg == "--number") {
            options.enableNumbering = true;
        }
        else if (arg == "--start" && i + 1 < argc) {
            try {
                options.startNumber = std::stoi(argv[++i]);
            } catch (const std::exception&) {
                std::cerr << "Error: --start must be a valid integer" << std::endl;
                return false;
            }
        }
        else if (arg == "--width" && i + 1 < argc) {
            try {
                options.numberWidth = std::stoi(argv[++i]);
            } catch (const std::exception&) {
                std::cerr << "Error: --width must be a valid integer" << std::endl;
                return false;
            }
        }
        else if ((arg == "--input") || (arg == "--ext") || (arg == "--keyword") ||
                 (arg == "--prefix") || (arg == "--suffix") || (arg == "--replace") ||
                 (arg == "--with") || (arg == "--start") || (arg == "--width")) {
            std::cerr << "Error: Missing value for option " << arg << std::endl;
            return false;
        }
        else if (arg[0] == '-') {
            std::cerr << "Unknown option: " << arg << std::endl;
            return false;
        }
    }
    return true;
}

bool validateOptions(const CliOptions& options) {
    if (options.inputDir.empty()) {
        std::cerr << "Error: --input parameter is required" << std::endl;
        return false;
    }
    if (!options.previewMode && !options.executeMode) {
        std::cerr << "Error: Either --preview or --execute mode must be specified" << std::endl;
        return false;
    }
    if (options.previewMode && options.executeMode) {
        std::cerr << "Error: Cannot use both --preview and --execute modes together" << std::endl;
        return false;
    }
    if (!options.replaceTo.empty() && options.replaceFrom.empty()) {
        std::cerr << "Error: --replace parameter is required when using --with" << std::endl;
        return false;
    }
    if (!options.replaceFrom.empty() && options.replaceTo.empty()) {
        std::cerr << "Error: --with parameter is required when using --replace" << std::endl;
        return false;
    }
    if (options.enableNumbering && options.numberWidth <= 0) {
        std::cerr << "Error: --width must be greater than 0" << std::endl;
        return false;
    }
    return true;
}
