#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/* String Hashing (Single e Double Hash)
 * Hash polinomial para comparação de substrings em O(1) após build O(N).
 * Complexidade: O(N) build, O(1) query.
 * Memória: O(N)
 *
 * SingleHash: um par (MOD, BASE) — risco baixo de colisão para uso geral.
 * DoubleHash: dois pares independentes — colisão praticamente impossível.
 *
 * Uso:
 *   SingleHash h(s);
 *   h.get(l, r); // hash de s[l..r]
 *   h.get(l, r) == h.get(l2, r2); // compara substrings
 */

/* --- Single Hash --- */
struct SingleHash {
    static const ll MOD = (1LL << 61) - 1;
    static const ll BASE;

    vector<ll> h, pw;

    static ll mul(ll a, ll b) {
        return (__uint128_t)a * b % MOD;
    }

    static ll add(ll a, ll b) {
        a += b;
        return a >= MOD ? a - MOD : a;
    }

    SingleHash() {}

    SingleHash(const string& s) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (int i = 0; i < (int)s.size(); i++) {
            h[i + 1] = add(mul(h[i], BASE), s[i]);
            pw[i + 1] = mul(pw[i], BASE);
        }
    }

    ll get(int l, int r) const {
        return add(h[r + 1], MOD - mul(h[l], pw[r - l + 1]));
    }
};

const ll SingleHash::BASE = []() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(1e9, SingleHash::MOD - 1)(rng);
}();

/* --- Double Hash --- */
struct DoubleHash {
    static const ll MOD1 = (1LL << 61) - 1;
    static const ll MOD2 = 1e9 + 9;
    static const ll BASE1, BASE2;

    vector<ll> h1, h2, pw1, pw2;

    static ll mul1(ll a, ll b) { return (__uint128_t)a * b % MOD1; }
    static ll add1(ll a, ll b) { a += b; return a >= MOD1 ? a - MOD1 : a; }
    static ll mul2(ll a, ll b) { return (__int128)a * b % MOD2; }
    static ll add2(ll a, ll b) { a += b; return a >= MOD2 ? a - MOD2 : a; }

    DoubleHash() {}

    DoubleHash(const string& s)
        : h1(s.size() + 1, 0), h2(s.size() + 1, 0),
          pw1(s.size() + 1, 1), pw2(s.size() + 1, 1) {
        for (int i = 0; i < (int)s.size(); i++) {
            h1[i + 1] = add1(mul1(h1[i], BASE1), s[i]);
            h2[i + 1] = add2(mul2(h2[i], BASE2), s[i]);
            pw1[i + 1] = mul1(pw1[i], BASE1);
            pw2[i + 1] = mul2(pw2[i], BASE2);
        }
    }

    // retorna par de hashes de s[l..r] (0-indexed, inclusive)
    pair<ll, ll> get(int l, int r) const {
        ll v1 = add1(h1[r + 1], MOD1 - mul1(h1[l], pw1[r - l + 1]));
        ll v2 = add2(h2[r + 1], MOD2 - mul2(h2[l], pw2[r - l + 1]));
        return {v1, v2};
    }
};

const ll DoubleHash::BASE1 = []() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    return uniform_int_distribution<ll>(1e9, DoubleHash::MOD1 - 1)(rng);
}();

const ll DoubleHash::BASE2 = []() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() + 1);
    return uniform_int_distribution<ll>(1e9, DoubleHash::MOD2 - 1)(rng);
}();
