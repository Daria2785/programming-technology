#pragma execution_character_set("utf-8")

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <limits>

#define NOMINMAX
#include <windows.h>

#include "textAnalyz.h"
#include "NumbProcess.h"

template<typename Func>
void measureTime(const std::string& label, Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "[" << label << "] Время: " << us << " мкс\n";
}

void printVector(const std::string& label, const std::vector<int>& v) {
    std::cout << label << ": ";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << "\n";
}

void printMenu() {
    std::cout << "\nМеню\n";
    std::cout << "1. Задание 1 - подсчёт уникальных слов\n";
    std::cout << "2. Задание 2 - индексация позиций слов\n";
    std::cout << "3. Задание 3a - возведение простых чисел в квадрат\n";
    std::cout << "4. Задание 3b - сортировка (нечётные, чётные)\n";
    std::cout << "5. Задание 3c - уникальные числа в диапазоне\n";
    std::cout << "6. Выполнить ВСЕ задания\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}


void runTask1(TextAnalyzer& analyzer) {
    std::cout << "\nЗадание 1: уникальные слова\n";
    measureTime("Подсчёт уникальных слов", [&]() {
        analyzer.countUniqueWords();
        });
}

void runTask2(TextAnalyzer& analyzer) {
    std::cout << "\nЗадание 2: позиции слов\n";
    measureTime("Индексация позиций слов", [&]() {
        analyzer.indexWordPositions();
        });
}

void runTask3a() {
    std::cout << "\nЗадание 3a: простые числа в квадрат\n";
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    printVector("3a вход", data);
    measureTime("3a возведение простых в квадрат", [&]() {
        auto res = NumberProcessor::squarePrimes(data);
        printVector("3a выход", res);
        });
}

void runTask3b() {
    std::cout << "\nЗадание 3b: сортировка нечётных/чётных\n";
    std::vector<int> data = { 5, 2, 9, 1, 7, 4, 8, 3, 6, 0, 11, 12 };
    printVector("3b вход", data);
    measureTime("3b сортировка нечётных/чётных", [&]() {
        auto res = NumberProcessor::sortOddEven(data);
        printVector("3b выход", res);
        });
}

void runTask3c() {
    std::cout << "\nЗадание 3c: уникальные в диапазоне\n";
    std::vector<int> data = { 1, 5, 3, 8, 5, 12, 7, 5, 20, -3, 0, 15 };
    printVector("3c вход", data);
    measureTime("3c уникальные в диапазоне", [&]() {
        auto res = NumberProcessor::uniqueInRange(data, 0, 10);
        printVector("3c выход (диапазон 0..10)", res);
        });
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const std::string filename = "war1.txt";
    TextAnalyzer analyzer(filename);
    if (!analyzer.load()) {
        std::cerr << "Не удалось открыть файл: " << filename << "\n";
        return 1;
    }

    int choice = -1;
    while (true) {
        printMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Введите число.\n";
            continue;
        }

        switch (choice) {
        case 1:
            runTask1(analyzer);
            break;
        case 2:
            runTask2(analyzer);
            break;
        case 3:
            runTask3a();
            break;
        case 4:
            runTask3b();
            break;
        case 5:
            runTask3c();
            break;
        case 6:
            runTask1(analyzer);
            runTask2(analyzer);
            runTask3a();
            runTask3b();
            runTask3c();
            break;
        case 0:
            std::cout << "Выход из программы.\n";
            return 0;
        default:
            std::cout << "Неизвестный пункт. Попробуйте снова.\n";
        }
    }

    return 0;
}