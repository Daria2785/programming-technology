#include "FormValidator.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <cctype>
#include <windows.h> // For MultiByteToWideChar and CharLowerBuffW

// Helper functions for UTF-8 <-> Wide String conversion
std::wstring utf8_to_wstring(const std::string& str) {
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

std::string wstring_to_utf8(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

Person FormValidator::inputUserData(const std::string& rawName, const std::string& rawDate,
    const std::string& rawPhone, const std::string& rawEmail) {
    return { rawName, rawDate, rawPhone, rawEmail };
}

Person FormValidator::validate(const Person& raw) {
    Person result;

    // 1. Full Name
    std::wstring wName = utf8_to_wstring(raw.fullName);
    std::wstring wCleanName;
    std::wstring wCurrentWord;

    for (size_t i = 0; i <= wName.size(); ++i) {
        if (i == wName.size() || wName[i] == L' ') {
            if (!wCurrentWord.empty()) {
                // Clean from digits and garbage
                std::wstring wWordOnlyLetters;
                for (wchar_t c : wCurrentWord) {
                    if (iswalpha(c)) wWordOnlyLetters += c;
                }

                if (!wWordOnlyLetters.empty()) {
                    // Make the first letter uppercase
                    wWordOnlyLetters[0] = towupper(wWordOnlyLetters[0]);

                    // Make the rest lowercase using a reliable Windows function
                    if (wWordOnlyLetters.size() > 1) {
                        CharLowerBuffW(&wWordOnlyLetters[1], (DWORD)(wWordOnlyLetters.size() - 1));
                    }

                    wCleanName += wWordOnlyLetters + L" ";
                }
                wCurrentWord.clear();
            }
        }
        else {
            wCurrentWord += wName[i];
        }
    }
    if (!wCleanName.empty()) wCleanName.pop_back(); // Remove the last space
    result.fullName = wstring_to_utf8(wCleanName);

    // 2. Date
    std::string digits;
    for (char c : raw.birthDate) {
        if (std::isdigit(c)) digits += c;
    }
    if (digits.length() == 8) {
        result.birthDate = digits.substr(6, 2) + "." + digits.substr(4, 2) + "." + digits.substr(0, 4);
    }
    else {
        result.birthDate = "Invalid date format";
    }

    // 3. Phone
    result.phone = "";
    for (char c : raw.phone) {
        if (std::isdigit(c) || c == '+') {
            result.phone += c;
        }
    }

    // 4. Email
    result.email = raw.email;
    for (size_t i = 0; i < result.email.size(); ++i) {
        if (result.email[i] >= 'A' && result.email[i] <= 'Z') {
            result.email[i] = result.email[i] + 32;
        }
    }

    return result;
}

Person FormValidator::generateRandom() {
    std::vector<std::string> surnames = { "Ivanov", "Sidorov", "Petrov", "Smirnov", "Kuznetsov" }; // Kept in Russian for generation
    std::vector<std::string> names = { "Ivan", "Petr", "Aleksey", "Dmitriy", "Sergey" };
    std::vector<std::string> patronymics = { "Ivanovich", "Petrovich", "Alekseevich", "Dmitrievich", "Sergeevich" };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 4);

    std::string fio = surnames[dist(gen)] + " " + names[dist(gen)] + " " + patronymics[dist(gen)];

    std::uniform_int_distribution<> yearDist(1970, 2005);
    std::uniform_int_distribution<> monthDist(1, 12);
    std::uniform_int_distribution<> dayDist(1, 28);

    int year = yearDist(gen);
    int month = monthDist(gen);
    int day = dayDist(gen);

    std::string yearStr = std::to_string(year);
    std::string monthStr = (month < 10 ? "0" : "") + std::to_string(month);
    std::string dayStr = (day < 10 ? "0" : "") + std::to_string(day);

    std::string date = yearStr + "-" + monthStr + "-" + dayStr;

    std::string phone = "+7999" + std::to_string(1000000 + dist(gen) * 12345);
    std::string email = "user" + std::to_string(dist(gen)) + "@mail.ru";

    return { fio, date, phone, email };
}