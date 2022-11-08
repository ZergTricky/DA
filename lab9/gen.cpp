#include "bits/stdc++.h"

using namespace std;

int main(int argc, char **argv) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    if (argc < 3) {
        cout << "Bad args!\n";
        return 0;
    }
    int n = stoi(argv[1]), m = stoi(argv[2]);
    cout << n << " " << m << "\n";
    for (int i = 0; i < m; ++i) {
        int u = rng() % n + 1, v = rng() % n + 1;
        while (u == v) {
            u = rng() % n + 1;
            v = rng() % n + 1;
        }
        cout << u << " " << v << "\n";
    }

    return 0;
}
