#include "NumbProcess.h"

#include <algorithm>
#include <set>

bool NumberProcessor::isPrime(int n) {
    if (n < 2) return false;
    if (n < 4) return true;        
    if (n % 2 == 0) return false;  
    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

std::vector<int> NumberProcessor::squarePrimes(std::vector<int> data) {
    std::transform(data.begin(), data.end(), data.begin(),
        [](int x) {
            return isPrime(x) ? x * x : x;
        });
    return data;
}

std::vector<int> NumberProcessor::sortOddEven(std::vector<int> data) {
    std::sort(data.begin(), data.end(),
        [](int a, int b) {
            bool aOdd = (a % 2 != 0);
            bool bOdd = (b % 2 != 0);
            if (aOdd != bOdd) return aOdd;   // odd before even
            if (aOdd) return a < b;          // odd ascending
            return a > b;                    // even descending
        });
    return data;
}

std::vector<int> NumberProcessor::uniqueInRange(const std::vector<int>& data,
    int low, int high) {
    std::set<int> uniq;
    for (int x : data) {
        if (x >= low && x <= high) {
            uniq.insert(x);
        }
    }
    return std::vector<int>(uniq.begin(), uniq.end());
}