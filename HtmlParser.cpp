#include "HtmlParser.h"
#include <iostream>
#include <regex>

bool HtmlParser::validate(const std::string& text) {
    // 1. Check if there are any tags at all
    std::regex tagRegex("<[^>]+>");
    if (!std::regex_search(text, tagRegex)) {
        std::cerr << "[Error] Text does not contain HTML tags.\n";
        return false;
    }

    // 2. Check for markers of other languages (Markdown)
    if (text.find("# ") != std::string::npos || text.find("**") != std::string::npos) {
        std::cerr << "[Error] Text looks like Markdown, not HTML.\n";
        return false;
    }

    // 3. Check for mandatory HTML tags (html, body)
    std::regex htmlTagRegex("<html[^>]*>", std::regex::icase);
    std::regex bodyTagRegex("<body[^>]*>", std::regex::icase);

    bool hasHtml = std::regex_search(text, htmlTagRegex);
    bool hasBody = std::regex_search(text, bodyTagRegex);

    if (!hasHtml || !hasBody) {
        std::cerr << "[Error] Text is not valid HTML (missing <html> or <body> tags).\n";
        return false;
    }

    return true;
}

std::vector<std::string> HtmlParser::findHeadings(const std::string& text) {
    std::vector<std::string> headings;
    // [\s\S]*? matches any character including newlines
    std::regex headingRegex("<h[1-6]>([\\s\\S]*?)</h[1-6]>");

    auto begin = std::sregex_iterator(text.begin(), text.end(), headingRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        headings.push_back((*i)[1].str());
    }
    return headings;
}

std::vector<std::string> HtmlParser::findParagraphs(const std::string& text) {
    std::vector<std::string> paragraphs;
    std::regex pRegex("<p>([\\s\\S]*?)</p>");

    auto begin = std::sregex_iterator(text.begin(), text.end(), pRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        paragraphs.push_back((*i)[1].str());
    }
    return paragraphs;
}

std::vector<std::string> HtmlParser::findLists(const std::string& text) {
    std::vector<std::string> lists;
    // Flag icase makes the search case-insensitive (UL, ul, Ol)
    std::regex listRegex("<(ul|ol)>([\\s\\S]*?)</(ul|ol)>", std::regex::icase);

    auto begin = std::sregex_iterator(text.begin(), text.end(), listRegex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        lists.push_back((*i)[2].str());
    }
    return lists;
}