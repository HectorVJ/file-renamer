#include "cli.h"
#include "file_scanner.h"
#include "file_filter.h"
#include "rename_rule.h"
#include "rename_executor.h"
#include "report_writer.h"
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

    std::vector<std::pair<FileEntry, std::string>> renamePairs;
    for (size_t i = 0; i < filteredFiles.size(); ++i) {
        std::string newName = rule.apply(filteredFiles[i].filename, filteredFiles[i].extension, i);
        renamePairs.push_back({filteredFiles[i], newName});
    }

    RenameExecutor executor;
    int conflicts = executor.detectConflicts(renamePairs);
    std::cout << "Conflicts detected: " << conflicts << std::endl;

    if (conflicts > 0 && options.executeMode) {
        std::cout << "Warning: Skipping rename due to conflicts. Use --preview to check results." << std::endl;
        return 1;
    }

    std::vector<RenameResult> results;
    
    if (options.previewMode) {
        std::cout << "\nRename preview:" << std::endl;
        for (const auto& pair : renamePairs) {
            std::cout << "  " << pair.first.filename << " -> " << pair.second << std::endl;
        }
        results = executor.preview(renamePairs);
    } else if (options.executeMode) {
        std::cout << "\nExecuting rename:" << std::endl;
        results = executor.execute(renamePairs);
        int successCount = 0;
        int failCount = 0;
        for (const auto& r : results) {
            if (r.success) successCount++;
            else failCount++;
        }
        std::cout << "Rename completed. Success: " << successCount << ", Failed: " << failCount << std::endl;
    }

    ReportWriter writer;
    writer.writeReport(results, "rename_report.md");

    return 0;
}