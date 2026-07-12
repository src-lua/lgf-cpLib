#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* Convex Hull Trick dinâmico (LineContainer) — O(log N) por operação
 *
 * Mantém um conjunto de retas y = k·x + m e responde o MÁXIMO em um x.
 * Insere e consulta em qualquer ordem — k e x arbitrários, sem precisar
 * de monotonicidade.
 *
 * Quando usar: DP do tipo dp[i] = max_j (k[j]·x[i] + m[j]) — cada estado vira
 * uma reta add(k[j], m[j]) e a transição é uma query(x[i]).
 *
 *   add(k, m)  → insere a reta y = k·x + m
 *   query(x)   → maior valor entre todas as retas em x
 *
 * Para MÍNIMO: insira add(-k, -m) e use -query(x).
 */

struct Line {
    ll k, m; mutable ll p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
