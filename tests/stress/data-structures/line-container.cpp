#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/data-structures/line-container.hpp"

int main() {
    mt19937 rng(16);
    for (int t = 0; t < 5000; t++) {
        LineContainer lc;
        vector<pair<ll,ll>> lines;
        int nl = 1 + rng() % 8;
        for (int i = 0; i < nl; i++) {
            ll k = (ll)(rng() % 41) - 20, m = (ll)(rng() % 201) - 100;
            lc.add(k, m); lines.push_back({k, m});
        }
        for (int q = 0; q < 6; q++) {
            ll x = (ll)(rng() % 81) - 40, best = LLONG_MIN;
            for (auto [k, m] : lines) best = max(best, k * x + m);
            assert(lc.query(x) == best);
        }
    }
    puts("line-container (CHT): query max vs brute, 5k casos");
    return 0;
}
