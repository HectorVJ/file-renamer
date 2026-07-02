#ifndef REPORT_WRITER_H
#define REPORT_WRITER_H

#include "rename_executor.h"
#include <vector>
#include <string>

class ReportWriter {
public:
    bool writeReport(const std::vector<RenameResult>& results, const std::string& outputPath);
};

#endif