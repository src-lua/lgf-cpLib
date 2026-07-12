#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/math/number-theory.hpp"

int main() {
    // CRT vs brute
    for (int m1 = 1; m1 <= 25; m1++)
        for (int m2 = 1; m2 <= 25; m2++)
            for (int a1 = 0; a1 < m1; a1++)
                for (int a2 = 0; a2 < m2; a2++) {
                    auto [r, l] = crt(a1, m1, a2, m2);
                    ll g = __gcd((ll)m1, (ll)m2), L = (ll)m1 / g * m2;
                    ll found = -1;
                    for (ll x = 0; x < L; x++) if (x % m1 == a1 && x % m2 == a2) { found = x; break; }
                    if (found == -1) assert(l == 0);           // sem solucao
                    else { assert(l == L && r == found); }     // menor solucao + lcm
                }
    // factorize + divisors vs brute
    for (ll n = 1; n <= 3000; n++) {
        auto f = factorize(n);
        ll prod = 1; for (auto [p, e] : f) for (int i = 0; i < e; i++) prod *= p;
        assert(prod == n);
        auto d = divisors(n); // ja ordenado
        vector<ll> bd; for (ll i = 1; i <= n; i++) if (n % i == 0) bd.push_back(i);
        assert(d == bd);
    }
    puts("number-theory: crt (~390k pares) + factorize/divisors 1..3000");
    return 0;
}
