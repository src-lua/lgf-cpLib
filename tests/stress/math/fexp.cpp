#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/math/fexp.hpp"

int main() {
    mt19937_64 rng(1);
    const ll MOD = 998244353;
    for (int t = 0; t < 100000; t++) {
        ll a = rng() % MOD, b = rng() % 1000;
        ll ref = 1, aa = a % MOD;
        for (ll i = 0; i < b; i++) ref = (__int128)ref * aa % MOD;
        assert(fexp(a, b, MOD) == ref);
    }
    for (ll a = 1; a <= 2000; a++) assert((ll)((__int128)a * modinv(a, MOD) % MOD) == 1);
    const ll BIG = 2000000011LL; // primo > 2^30
    for (ll a = 1; a <= 2000; a++) assert((ll)((__int128)a * modinv(a, BIG) % BIG) == 1);
    puts("fexp/modinv: 100k potencias + 4k inversos (2 mods)");
    return 0;
}
