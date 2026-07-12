#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/math/convolutions/ntt.hpp"

int main() {
    using N = NTT<998244353, 3>;
    const ll MOD = 998244353;
    mt19937 rng(5);
    for (int t = 0; t < 300; t++) {
        int n = 1 + rng() % 60, m = 1 + rng() % 60;
        vector<ll> a(n), b(m);
        for (auto& x : a) x = rng() % MOD;
        for (auto& x : b) x = rng() % MOD;
        auto c = N::conv(a, b);
        vector<ll> ref(n + m - 1, 0);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            ref[i + j] = (ref[i + j] + (__int128)a[i] * b[j]) % MOD;
        assert(c == ref);
    }
    puts("ntt: conv vs O(n^2), 300 casos");
    return 0;
}
