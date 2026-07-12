#include <bits/stdc++.h>
using namespace std;
#include "lib/graphs/2sat.hpp"

int main() {
    mt19937 rng(7);
    for (int t = 0; t < 3000; t++) {
        int n = 1 + rng() % 6, m = rng() % 12;
        vector<array<int,4>> cl; // {va, pa, vb, pb} : (x_va == pa) OR (x_vb == pb)
        TwoSat ts(n);
        for (int i = 0; i < m; i++) {
            int va = rng() % n, pa = rng() % 2, vb = rng() % n, pb = rng() % 2;
            cl.push_back({va, pa, vb, pb});
            ts.add_or(pa ? va : ~va, pb ? vb : ~vb);
        }
        auto [sat, ans] = ts.solve();
        bool anySat = false;
        for (int mask = 0; mask < (1 << n) && !anySat; mask++) {
            bool ok = true;
            for (auto& c : cl) {
                bool la = (((mask >> c[0]) & 1) == c[1]);
                bool lb = (((mask >> c[2]) & 1) == c[3]);
                if (!(la || lb)) { ok = false; break; }
            }
            if (ok) anySat = true;
        }
        assert(sat == anySat);
        if (sat) for (auto& c : cl) assert((ans[c[0]] == c[1]) || (ans[c[2]] == c[3]));
    }
    puts("2sat: SAT/UNSAT + assignment valido vs brute 2^n, 3k casos");
    return 0;
}
