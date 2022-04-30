#include "bits/stdc++.h"

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int STRING_SIZE = 20;

string GenString() {
    string res;
    for (int i = 0; i < STRING_SIZE; ++i) {
        res += (char) (rng() % 26 + 'a');
    }
    return res;
}

unsigned long long GenValue() {
    return rng();
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 0;
    }
    int n = stoi(argv[1]);
    vector<string> all;
    for (int i = 0; i < n; ++i) {
        string s = GenString();
        all.push_back(s);
        cout << "+ " << s << " " << GenValue() << "\n";
    }
    shuffle(all.begin(), all.end(), rng);
    for (int i = 0; i < n; ++i) {
        if (rng() % 2) {
            cout << all[rng() % all.size()] << "\n";
        } else {
            cout << "- " << all.back() << "\n";
            all.pop_back();
        }
    }
    return 0;
}
