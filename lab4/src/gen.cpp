#include <bits/stdc++.h>

using namespace std;

#define flush cout.flush

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pl = pair<ll, ll>;
const ll INF = 1e9 + 7;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ld eps = 1e-9;
const ld PI = acos(-1);

const int K = 12;
const int N = 50000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < K; ++i) {
        if (rng() % 3 == 0) {
            cout << "? ";
        } else cout << (rng() % 2 ? UINT32_MAX : 1355) << " ";
    }
    cout << "\n";
    for (int i = 0; i < N; ++i) {
        if (rng() % 100 == 0)cout << "\n";
        cout << (rng() % 2 ? UINT32_MAX : 1355) << " ";
    }
    return 0;
}