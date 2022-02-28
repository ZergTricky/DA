#include "iostream"
#include "vector"
#include "iomanip"
#include "BucketSort.hpp"

const int LOWER_BOUND = -100;
const int UPPER_BOUND = 100;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<std::pair<double, std::string>> inputVector;
    double key;
    std::string value;
    while (std::cin >> key) {
        std::cin >> std::ws;
        std::getline(std::cin, value);
        inputVector.push_back({key, value});
    }
    inputVector = BucketSort::sort(inputVector, LOWER_BOUND, UPPER_BOUND);
    std::cout << std::fixed << std::setprecision(6);
    for (const std::pair<double, std::string> &item : inputVector) {
        std::cout << item.first << "\t" << item.second << "\n";
    }
    return 0;
}