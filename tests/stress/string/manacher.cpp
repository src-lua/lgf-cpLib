#include <bits/stdc++.h>
using namespace std;
#include "lib/string/manacher.hpp"

int main() {
    mt19937 rng(14);
    for (int t = 0; t < 3000; t++) {
        int len = 1 + rng() % 25, sig = 1 + rng() % 3;
        string s; for (int i = 0; i < len; i++) s += char('a' + rng() % sig);
        palindrome<string> p(s);
        int n = s.size();
        for (int i = 0; i < n; i++) for (int j = i; j < n; j++) {
            bool isPal = true;
            for (int a = i, b = j; a < b; a++, b--) if (s[a] != s[b]) { isPal = false; break; }
            assert(p.query(i, j) == isPal);
        }
    }
    puts("manacher: palindrome::query vs brute (todos os pares), 3k casos");
    return 0;
}
