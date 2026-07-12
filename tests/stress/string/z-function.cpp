#include <bits/stdc++.h>
using namespace std;
#include "lib/string/z-function.hpp"

int main() {
    mt19937 rng(13);
    for (int t = 0; t < 5000; t++) {
        int len = 1 + rng() % 20, sig = 1 + rng() % 3;
        string s; for (int i = 0; i < len; i++) s += char('a' + rng() % sig);
        auto z = z_function(s);
        int n = s.size();
        assert(z[0] == 0);
        for (int i = 1; i < n; i++) { int k = 0; while (i + k < n && s[k] == s[i + k]) k++; assert(z[i] == k); }
        int m = 1 + rng() % len;
        string p = s.substr(rng() % (len - m + 1), m);
        auto occ = z_search(p, s);
        vector<int> b;
        for (int i = 0; i + m <= (int)s.size(); i++) if (s.substr(i, m) == p) b.push_back(i);
        assert(occ == b);
    }
    puts("z-function: z + z_search vs brute, 5k casos");
    return 0;
}
