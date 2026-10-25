#pragma once
#include <string>

struct Person {
    std::string fullName;
    std::string birthDate;
    std::string phone;
    std::string email;
};

// Class for validating user form data and generating random forms
class FormValidator {
public:
    // Task 3a: Input user data
    static Person inputUserData(const std::string& rawName, const std::string& rawDate,
        const std::string& rawPhone, const std::string& rawEmail);

    // Task 3b: Validate and format data
    static Person validate(const Person& rawPerson);

    // Task 3c: Generate random data
    static Person generateRandom();
};