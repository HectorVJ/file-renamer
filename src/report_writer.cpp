#include "report_writer.h"
#include <fstream>
#include <iostream>

bool ReportWriter::writeReport(const std::vector<RenameResult>& results, const std::string& outputPath) {
    std::ofstream ofs(outputPath);
    if (!ofs) {
        std::cerr << "Failed to create report file: " << outputPath << std::endl;
        return false;
    }

    ofs << "# File Rename Report\n\n";
    ofs << "| Old Name | New Name | Status | Error |\n";
    ofs << "|----------|----------|--------|-------|\n";

    for (const auto& r : results) {
        ofs << r.oldPath << " | " << r.newPath << " | ";
        ofs << (r.success ? "Success" : "Failed") << " | ";
        ofs << (r.success ? "-" : r.errorMessage) << "\n";
    }

    ofs.close();
    std::cout << "Report written to: " << outputPath << std::endl;
    return true;
}