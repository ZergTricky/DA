#include "iostream"
#include "vector"

int main() {
    long long n, p, m;
    std::cin >> n >> p >> m;
    std::vector<long long> val(n, -1);
    long long current = 1;
    for (int i = 0; i < n; ++i) {
        if (current > m)break;
        val[i] = current;
        current *= p;
    }
    std::vector<long long> res(n);
    for (int i = n - 1; i >= 0; --i) {
        if (val[i] == -1) {
            res[i] = 0;
        } else {
            res[i] = m / val[i];
            m %= val[i];
        }
    }
    for (const long long &v: res) {
        std::cout << v << "\n";
    }
    return 0;
}