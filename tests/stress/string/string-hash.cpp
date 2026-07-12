#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/string/string-hash.hpp"

int main() {
    mt19937 rng(11);
    for (int t = 0; t < 500; t++) {
        int len = 1 + rng() % 60, sig = 1 + rng() % 4;
        string s; for (int i = 0; i < len; i++) s += char('a' + rng() % sig);
        SingleHash sh(s); DoubleHash dh(s);
        for (int q = 0; q < 60; q++) {
            int l1 = rng() % len, r1 = rng() % len; if (l1 > r1) swap(l1, r1);
            int l2 = rng() % len, r2 = rng() % len; if (l2 > r2) swap(l2, r2);
            bool eq = (r1 - l1 == r2 - l2) && s.substr(l1, r1 - l1 + 1) == s.substr(l2, r2 - l2 + 1);
            bool sEq = (r1 - l1 == r2 - l2) && sh.get(l1, r1) == sh.get(l2, r2);
            bool dEq = (r1 - l1 == r2 - l2) && dh.get(l1, r1) == dh.get(l2, r2);
            if (eq) assert(sEq && dEq);   // hashes iguais quando as strings sao iguais
            assert(dEq == eq);            // double hash: sem colisao no teste
        }
    }
    puts("string-hash: single (sem falso-neg) + double (==) vs compare, 500 casos");
    return 0;
}
