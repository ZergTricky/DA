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

string good(const string &a) {
    if (a == "?")return a;
    ll x = stoll(a);
    return to_string(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<string> pattern;
    string s;
    getline(cin, s);
    string cur;
    for (auto &c : s) {
        if ((c >= '0' && c <= '9') || c == '?') {
            cur += c;
        } else {
            if (!cur.empty())pattern.push_back(good(cur));
            cur.clear();
        }
    }
    if (!cur.empty())pattern.push_back(good(cur));
    vector<string> text;
    vector<pl> pos;
    ll row = 0;
    while (getline(cin, s)) {
        cur.clear();
        ll col = 0;
        for (auto &c : s) {
            if (c >= '0' && c <= '9') {
                cur += c;
            } else {
                if (!cur.empty()) {
                    text.push_back(good(cur));
                    pos.push_back({row, col++});
                }
                cur.clear();
            }
        }
        if (!cur.empty()) {
            text.push_back(good(cur));
            pos.push_back({row, col++});
        }
        ++row;
    }
    for (ll i = 0; i + pattern.size() - 1 < text.size(); ++i) {
        bool ok = true;
        for (ll j = 0; j < pattern.size(); ++j) {
            if (pattern[j] == "?")continue;
            if (pattern[j] != text[i + j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << pos[i].first + 1 << ", " << pos[i].second + 1 << "\n";
        }
    }
    return 0;
}