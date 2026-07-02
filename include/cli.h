#ifndef CLI_H
#define CLI_H

#include <string>

struct CliOptions {
    std::string inputDir;
    bool previewMode = false;
    bool executeMode = false;
    std::string extensionFilter;
    std::string prefix;
    std::string suffix;
    std::string replaceFrom;
    std::string replaceTo;
    bool enableNumbering = false;
    int startNumber = 1;
    int numberWidth = 3;
};

bool parseArguments(int argc, char* argv[], CliOptions& options);
void printUsage(const char* programName);
bool validateOptions(const CliOptions& options);

#endif