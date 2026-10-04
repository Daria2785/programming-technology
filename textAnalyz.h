#pragma once

#include <string>
#include <map>
#include <vector>

class TextAnalyzer {
public:
    explicit TextAnalyzer(const std::string& filename);
    bool load();
    void countUniqueWords() const;
    void indexWordPositions() const;

private:
    std::string filename_;
    std::vector<std::string> words_;
};