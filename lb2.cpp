#pragma execution_character_set("utf-8")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#define NOMINMAX
#include <windows.h>

#include "HtmlParser.h"
#include "FormValidator.h"

// Universal function to read and validate a file
void checkFile(const std::string& filename) {
    std::cout << "\n=== CHECKING FILE: " << filename << " ===\n";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open file " << filename << " (place it next to the .exe)\n";
        return;
    }

    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    if (HtmlParser::validate(text)) {
        std::cout << "SUCCESS: This is a valid HTML file.\n\n";

        auto h = HtmlParser::findHeadings(text);
        std::cout << "Found headings: " << h.size() << "\n";
        for (const auto& x : h) std::cout << " - " << x << "\n";

        auto p = HtmlParser::findParagraphs(text);
        std::cout << "Found paragraphs: " << p.size() << "\n";
        for (const auto& x : p) std::cout << " - " << x << "\n";

        auto l = HtmlParser::findLists(text);
        std::cout << "Found lists: " << l.size() << "\n";
        for (const auto& x : l) std::cout << " - " << x << "\n";
    }
}

void printMenu() {
    std::cout << "\n============ LAB 2 ============\n";
    std::cout << "1. Check valid file (test.html)\n";
    std::cout << "2. Check invalid file (wrong.html)\n";
    std::cout << "3. Validate form manually\n";
    std::cout << "4. Generate random form\n";
    std::cout << "0. Exit\n";
    std::cout << "===============================\n";
    std::cout << "Your choice: ";
}

void testFormManually() {
    std::cout << "\n=== FORM TEST ===\n";
    std::string rawName = "Сидоров ИваН ПетРОви1ч";
    std::string rawDate = "2002-03-01";
    std::string rawPhone = "+7996-8432-431";
    std::string rawEmail = "sidorovVV@pochta.ru";

    Person raw = FormValidator::inputUserData(rawName, rawDate, rawPhone, rawEmail);
    Person clean = FormValidator::validate(raw);

    std::cout << "Input data: " << rawName << " " << rawDate << " " << rawPhone << " " << rawEmail << "\n\n";
    std::cout << "Cleaned data: " << clean.fullName << " " << clean.birthDate << " " << clean.phone << " " << clean.email << "\n";
}

void testFormRandom() {
    std::cout << "\n=== RANDOM FORM ===\n";
    Person raw = FormValidator::generateRandom();
    Person clean = FormValidator::validate(raw);
    std::cout << "Generated: " << clean.fullName << " " << clean.birthDate << " " << clean.phone << " " << clean.email << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int choice = -1;

    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: checkFile("test.html"); break;
        case 2: checkFile("wrong.html"); break;
        case 3: testFormManually(); break;
        case 4: testFormRandom(); break;
        case 0: return 0;
        default: std::cout << "Invalid input.\n";
        }
    }
    return 0;
}