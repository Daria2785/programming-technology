#pragma once
#include <string>
#include <vector>

class HtmlParser {
public:
    static bool validate(const std::string& text);
    static std::vector<std::string> findHeadings(const std::string& text);
    static std::vector<std::string> findParagraphs(const std::string& text);
    static std::vector<std::string> findLists(const std::string& text);
};
