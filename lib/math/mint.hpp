#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* mint — Inteiro modular
 * Complexidade: O(1) por operação, O(log mod) para inv()
 *
 * template<typename T, T mod>
 *
 * Uso comum:
 *   using mint = Mint<int, 998244353>;
 *   using mll  = Mint<ll, 998244353LL>;
 *
 * Operações: +, -, *, /, ==, !=, <<
 * inv() → inverso modular (mod deve ser primo)
 */

template<typename T, T mod>
struct Mint {
    T v;
    Mint(T v = 0) : v(((v % mod) + mod) % mod) {}

    Mint operator+(Mint o) const { return v+o.v >= mod ? v+o.v-mod : v+o.v; }
    Mint operator-(Mint o) const { return v-o.v < 0   ? v-o.v+mod : v-o.v; }
    Mint operator*(Mint o) const { return (ll)v * o.v % mod; }
    Mint operator/(Mint o) const { return *this * o.inv(); }

    Mint& operator+=(Mint o) { return *this = *this + o; }
    Mint& operator-=(Mint o) { return *this = *this - o; }
    Mint& operator*=(Mint o) { return *this = *this * o; }
    Mint& operator/=(Mint o) { return *this = *this / o; }

    bool operator==(Mint o) const { return v == o.v; }
    bool operator!=(Mint o) const { return v != o.v; }

    explicit operator T() const { return v; }

    Mint inv() const {
        T a = v, b = mod, x = 1, y = 0;
        while (b) { T q = a/b; a -= q*b; swap(a,b); x -= q*y; swap(x,y); }
        return x;
    }

    friend ostream& operator<<(ostream& os, Mint m) { return os << m.v; }
};
