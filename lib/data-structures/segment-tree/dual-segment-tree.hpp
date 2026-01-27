#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Dual Segment Tree (Range Update, Point Query)
 * Realiza atualizações em range e consultas pontuais.
 * Complexidade: O(log N) para update e get.
 * Memória: O(4*N)
 * Requisitos:
 * - TAG deve ter: compose(TAG), apply(T&) e construtor identidade.
 * - T é o tipo do dado nas folhas.
 * Exemplo de uso: DualSegTree<ll, MyTag> st(v);
 */

// --- Exemplo de TAG (Soma e Multiplicacao com Modulo) ---
/* 
struct Tag {
    ll mul = 1, add = 0;
    void compose(const Tag& t) {
        mul = (mul * t.mul) % MOD;
        add = (add * t.mul + t.add) % MOD;
    }
    void apply(ll& val) { val = (val * mul + add) % MOD; }
};
*/

template<typename T, typename TAG>
struct DualSegTree {
    int N;
    vector<TAG> lazy;
    vector<T> leaves;

    DualSegTree(int n) : N(n), lazy(4 * n), leaves(n) {}
    DualSegTree(const vector<T>& v)
        : N(v.size()), lazy(4 * v.size()), leaves(v) {}

    void push(int no, int l, int r) {
        int e = no << 1; 
        int d = e | 1;
        lazy[e].compose(lazy[no]);
        lazy[d].compose(lazy[no]);
        lazy[no] = TAG();
    }

    void update(int no, int l, int r, int a, int b, const TAG& v) {
        if (b < l || r < a) return;
        if (a <= l && r <= b) {
            lazy[no].compose(v);
            return;
        }
        push(no, l, r);
        int m = (l + r) >> 1;
        update(no << 1, l, m, a, b, v);
        update((no << 1) | 1, m + 1, r, a, b, v);
    }

    T get(int no, int l, int r, int idx) {
        if (l == r) {
            T res = leaves[idx];
            lazy[no].apply(res);
            return res;
        }
        push(no, l, r);
        int m = (l + r) >> 1;
        if (idx <= m) return get(no << 1, l, m, idx);
        else return get((no << 1) | 1, m + 1, r, idx);
    }

    void update(int l, int r, const TAG& t) { update(1, 0, N - 1, l, r, t); }
    T get(int idx) { return get(1, 0, N - 1, idx); }
};