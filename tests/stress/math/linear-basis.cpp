#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/math/linear-basis.hpp"

int main() {
    mt19937 rng(4);
    for (int t = 0; t < 3000; t++) {
        int n = rng() % 8;
        vector<ll> v(n);
        LinearBasis<ll, 20> lb;
        for (auto& x : v) { x = rng() % (1 << 20); lb.insert(x); }
        // brute: todos os XORs de subconjuntos
        set<ll> all; all.insert(0);
        for (ll x : v) { set<ll> ns = all; for (ll y : all) ns.insert(y ^ x); all = ns; }
        ll mx = 0; for (ll y : all) mx = max(mx, y);
        assert(lb.max_xor() == mx);
        assert((1 << lb.size()) == (int)all.size()); // rank == log2(#XORs)
        for (int q = 0; q < 6; q++) {
            ll x = rng() % (1 << 20);
            assert(lb.contains(x) == (all.count(x) > 0));
        }
    }
    puts("linear-basis: max_xor + size + contains vs subconjuntos, 3k casos");
    return 0;
}
