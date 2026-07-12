#include <bits/stdc++.h>
using namespace std;
#include "lib/string/kmp.hpp"

int main() {
    mt19937 rng(12);
    for (int t = 0; t < 5000; t++) {
        int len = 1 + rng() % 20, sig = 1 + rng() % 3;
        string s; for (int i = 0; i < len; i++) s += char('a' + rng() % sig);
        // failure vs brute
        auto f = kmp_failure(s);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            int best = 0;
            for (int k = 1; k <= i; k++) if (s.substr(0, k) == s.substr(i - k + 1, k)) best = k;
            assert(f[i] == best);
        }
        // search vs brute
        int m = 1 + rng() % len;
        string p = s.substr(rng() % (len - m + 1), m);
        auto occ = kmp_search(p, s);
        vector<int> b;
        for (int i = 0; i + m <= (int)s.size(); i++) if (s.substr(i, m) == p) b.push_back(i);
        assert(occ == b);
    }
    puts("kmp: failure + search vs brute, 5k casos");
    return 0;
}
