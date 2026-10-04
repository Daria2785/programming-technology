#pragma once

#include <vector>

// Static utilities for processing vector<int> with STL algorithms.
class NumberProcessor {
public:
    // Task 3a: if a number is prime, square it; otherwise leave as is.
    static std::vector<int> squarePrimes(std::vector<int> data);

    // Task 3b: sort so that odd numbers go first (ascending),
    // then even numbers (descending).
    static std::vector<int> sortOddEven(std::vector<int> data);

    // Task 3c: return unique elements from data that lie in [low, high].
    static std::vector<int> uniqueInRange(const std::vector<int>& data,
        int low, int high);

    // Helper: check if n is a prime number.
    static bool isPrime(int n);
};
