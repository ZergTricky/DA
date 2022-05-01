#include "iostream"
#include "map"
#include "string"

int main() {
    std::ios::sync_with_stdio(false);

    std::map<std::string, unsigned long long> mp;
    std::string c;
    while (std::cin >> c) {
        if (c == "+") {
            std::string key;
            std::cin >> key;
            unsigned long long value;
            std::cin >> value;
            if (mp.count(key)) {
                std::cout << "Exist\n";
            } else {
                mp[key] = value;
                std::cout << "OK\n";
            }
        } else if (c == "-") {
            std::string key;
            std::cin >> key;
            unsigned long long value;
            std::cin >> value;
            if (mp.count(key)) {
                mp.erase(key);
                std::cout << "OK\n";
            } else std::cout << "NoSuchWord\n";
        } else {
            if (mp.count(c)) {
                std::cout << "OK: " << mp[c] << "\n";
            } else std::cout << "NoSuchWord\n";
        }
    }
}
