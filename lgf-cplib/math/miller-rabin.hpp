#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* Miller-Rabin + Pollard Rho
 *
 * is_prime(n)  → O(log² n), determinístico para n < 3.3·10¹⁸
 * factorize(n) → O(n^{1/4} log n) esperado; fatores com repetição
 *
 * Use sort + unique para fatores distintos, ou agrupe por expoente.
 */

ll mulmod(ll a, ll b, ll m) { return (__int128)a * b % m; }

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    ll d = n - 1; int r = 0;
    while (d % 2 == 0) d /= 2, r++;
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= n) continue
        ll x = 1, base = a % n, exp = d;
        for (; exp > 0; exp >>= 1, base = mulmod(base, base, n))
            if (exp & 1) x = mulmod(x, base, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 0; i < r - 1; i++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    ll x = rand() % (n - 2) + 2, y = x, c = rand() % (n - 1) + 1, d = 1;
    while (d == 1) {
        x = (mulmod(x, x, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        d = __gcd(abs(x - y), n);
    }
    return d == n ? pollard_rho(n) : d;
}

vector<ll> factorize(ll n) {
    if (n == 1) return {};
    if (is_prime(n)) return {n};
    ll d = pollard_rho(n);
    auto a = factorize(d), b = factorize(n / d);
    a.insert(a.end(), b.begin(), b.end());
    return a;
}
