#include "textAnalyz.h"

#include <fstream>
#include <iostream>
#include <cctype>

namespace {

    std::string toLowerUtf8(const std::string& word) {
        std::string result;
        result.reserve(word.size());
        for (size_t i = 0; i < word.size(); ) {
            unsigned char c = static_cast<unsigned char>(word[i]);
            if (c < 128) {
                result += static_cast<char>(std::tolower(c));
                ++i;
                continue;
            }
            if (i + 1 < word.size() && (c == 0xD0 || c == 0xD1)) {
                unsigned char next = static_cast<unsigned char>(word[i + 1]);
                if (c == 0xD0 && next >= 0x90 && next <= 0xAF) {
                    result += static_cast<char>(0xD0);
                    result += static_cast<char>(next + 0x20);
                    i += 2;
                    continue;
                }
                if (c == 0xD0 && next == 0x81) {
                    result += static_cast<char>(0xD1);
                    result += static_cast<char>(0x91);
                    i += 2;
                    continue;
                }
                result += static_cast<char>(c);
                result += static_cast<char>(next);
                i += 2;
                continue;
            }
            result += static_cast<char>(c);
            ++i;
        }
        return result;
    }

    std::string keepOnlyLetters(const std::string& word) {
        std::string result;
        result.reserve(word.size());
        for (size_t i = 0; i < word.size(); ) {
            unsigned char c = static_cast<unsigned char>(word[i]);
            if (c < 128) {
                if (std::isalpha(c) || c == '-') {
                    result += static_cast<char>(c);
                }
                ++i;
                continue;
            }
            if (i + 1 < word.size() && (c == 0xD0 || c == 0xD1)) {
                unsigned char next = static_cast<unsigned char>(word[i + 1]);
                if (next >= 0x80 && next <= 0xBF) {
                    result += static_cast<char>(c);
                    result += static_cast<char>(next);
                    i += 2;
                    continue;
                }
            }
            ++i;
        }
        return result;
    }

} // namespace

TextAnalyzer::TextAnalyzer(const std::string& filename)
    : filename_(filename) {
}

bool TextAnalyzer::load() {
    std::ifstream file(filename_);
    if (!file.is_open()) return false;
    words_.clear();
    std::string rawWord;
    while (file >> rawWord) {
        std::string w = toLowerUtf8(keepOnlyLetters(rawWord));
        if (!w.empty()) words_.push_back(std::move(w));
    }
    return true;
}

void TextAnalyzer::countUniqueWords() const {
    std::map<std::string, int> freq;
    for (const auto& w : words_) freq[w]++;
    for (const auto& [word, count] : freq) {
        std::cout << word << " - " << count << "\n";
    }
    std::cout << "Общее количество уникальных слов: " << freq.size() << "\n";
}

void TextAnalyzer::indexWordPositions() const {
    std::map<std::string, std::vector<int>> positions;
    for (size_t i = 0; i < words_.size(); ++i) {
        positions[words_[i]].push_back(static_cast<int>(i));
    }
    for (const auto& [word, pos] : positions) {
        std::cout << word << " - ";
        for (size_t i = 0; i < pos.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << pos[i];
        }
        std::cout << "\n";
    }
}