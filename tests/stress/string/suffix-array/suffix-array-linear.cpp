#include <bits/stdc++.h>
using namespace std;
#include "lib/string/suffix-array/suffix-array-nlogn.hpp"
#include "lib/string/suffix-array/suffix-array-linear.hpp"

int main() {
    mt19937 rng(999);
    // equivalencia SA-IS vs O(n log n) (inclui alfabetos pequenos = muitos empates)
    for (int t = 0; t < 20000; t++) {
        int len = 1 + rng() % 14, sig = 1 + rng() % 3;
        string s; for (int i = 0; i < len; i++) s += char('a' + rng() % sig);
        SuffixArray a(s); SuffixArrayLinear b(s);
        assert(a.sa == b.sa && a.lcp == b.lcp);
    }
    // strings maiores + todos iguais (casos que quebravam o SA-IS)
    for (int t = 0; t < 500; t++) {
        int len = 1 + rng() % 200, sig = 1 + rng() % 26;
        string s; for (int i = 0; i < len; i++) s += char('a' + rng() % sig);
        SuffixArray a(s); SuffixArrayLinear b(s);
        assert(a.sa == b.sa && a.lcp == b.lcp);
    }
    for (int L = 1; L <= 60; L++) { string s(L, 'a'); SuffixArray a(s); SuffixArrayLinear b(s); assert(a.sa == b.sa); }
    puts("suffix-array linear (SA-IS): equivalente ao nlogn, 20k+ casos");
    return 0;
}
