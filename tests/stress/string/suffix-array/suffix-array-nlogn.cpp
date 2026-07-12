#include <bits/stdc++.h>
using namespace std;
#include "lib/string/suffix-array/suffix-array-nlogn.hpp"

int main() {
    mt19937 rng(10);
    for (int t = 0; t < 3000; t++) {
        int len = 1 + rng() % 12, sig = 1 + rng() % 3;
        string s; for (int i = 0; i < len; i++) s += char('a' + rng() % sig);
        SuffixArray sa(s);
        string ss = s + '$'; int n = ss.size();
        // sa vs ordenacao ingenua dos sufixos
        vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b) { return ss.substr(a) < ss.substr(b); });
        assert(sa.sa == idx);
        // lcp vs brute
        for (int i = 1; i < n; i++) { int h = 0; while (ss[sa.sa[i] + h] == ss[sa.sa[i-1] + h]) h++; assert(sa.lcp[i] == h); }
        // search: nº de ocorrencias
        int m = 1 + rng() % len;
        string p = s.substr(rng() % (len - m + 1), m);
        auto [lo, hi] = sa.search(p);
        int cnt = 0; for (int i = 0; i + m <= (int)s.size(); i++) if (s.substr(i, m) == p) cnt++;
        assert(hi - lo == cnt);
    }
    puts("suffix-array nlogn: sa + lcp + search vs brute, 3k casos");
    return 0;
}
