#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* fexp — Exponenciação rápida
 * Complexidade: O(log b)
 *
 * fexp(a, b) → a^b  usando operator* do tipo T
 *
 * Use com mint/mll para exponenciação modular automática.
 *
 * modinv<mod>(a) → a^{-1} % mod  (mod deve ser primo)
 */

template<typename T>
T fexp(T a, ll b) {
    T res = T(1);
    for (; b > 0; b >>= 1, a = a*a)
        if (b & 1) res = res * a;
    return res;
}

template<ll mod>
ll modinv(ll a) { return fexp<ll>(a % mod, mod - 2); }
