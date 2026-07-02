#ifndef RENAME_RULE_H
#define RENAME_RULE_H

#include <string>

class RenameRule {
public:
    void setPrefix(const std::string& prefix);
    void setSuffix(const std::string& suffix);
    void setReplaceFrom(const std::string& from);
    void setReplaceTo(const std::string& to);
    void setNumbering(bool enable, int start = 1, int width = 3);
    
    std::string apply(const std::string& filename, const std::string& extension, int index = 0) const;
    
private:
    std::string prefix_;
    std::string suffix_;
    std::string replaceFrom_;
    std::string replaceTo_;
    bool enableNumbering_ = false;
    int startNumber_ = 1;
    int numberWidth_ = 3;
    
    std::string formatNumber(int num) const;
};

#endif