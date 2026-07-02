#include "rename_rule.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

void RenameRule::setPrefix(const std::string& prefix) {
    prefix_ = prefix;
}

void RenameRule::setSuffix(const std::string& suffix) {
    suffix_ = suffix;
}

void RenameRule::setReplaceFrom(const std::string& from) {
    replaceFrom_ = from;
}

void RenameRule::setReplaceTo(const std::string& to) {
    replaceTo_ = to;
}

void RenameRule::setNumbering(bool enable, int start, int width) {
    enableNumbering_ = enable;
    startNumber_ = start;
    numberWidth_ = width;
}

std::string RenameRule::formatNumber(int num) const {
    std::ostringstream oss;
    oss << std::setw(numberWidth_) << std::setfill('0') << num;
    return oss.str();
}

std::string RenameRule::apply(const std::string& filename, const std::string& extension, int index) const {
    std::string result = filename;
    
    if (!replaceFrom_.empty()) {
        size_t pos = 0;
        while ((pos = result.find(replaceFrom_, pos)) != std::string::npos) {
            result.replace(pos, replaceFrom_.length(), replaceTo_);
            pos += replaceTo_.length();
        }
    }
    
    result = prefix_ + result;
    
    if (enableNumbering_) {
        result += formatNumber(startNumber_ + index);
    }
    
    result += suffix_;
    
    if (!extension.empty()) {
        result += "." + extension;
    }
    
    return result;
}