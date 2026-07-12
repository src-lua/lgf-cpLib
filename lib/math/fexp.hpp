#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* fexp — Exponenciação rápida modular
 * Complexidade: O(log b)
 *
 * fexp(a, b, mod) → a^b % mod
 * modinv(a, mod)  → a^{-1} % mod  (mod deve ser primo; usa Fermat)
 *
 * Usa __int128 no produto: seguro para mod até ~9.2·10¹⁸.
 */

ll fexp(ll a, ll b, ll mod) {
    a %= mod; if (a < 0) a += mod;
    ll res = 1;
    for (; b > 0; b >>= 1, a = (__int128)a * a % mod)
        if (b & 1) res = (__int128)res * a % mod;
    return res;
}

ll modinv(ll a, ll mod) { return fexp(a, mod - 2, mod); }
