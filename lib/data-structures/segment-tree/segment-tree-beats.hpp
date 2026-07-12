#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Segment Tree Beats (Range Update, Range Query)
 * Extensão da Lazy Seg Tree com condições de parada e de tag.
 * Complexidade amortizada: O(N log^2 N) para sequências de updates.
 * Memória: O(4*N)
 * Requisitos:
 * - NODE deve ter: static merge(L, R), apply(TAG, L, R),
 *   break_condition(TAG) e tag_condition(TAG),
 *   e construtor identidade.
 * - TAG deve ter: compose(TAG) e construtor identidade.
 *
 * break_condition(tag): retorna true se o update pode ser ignorado
 *                       (o nó já satisfaz a condição — ex: mx <= v).
 * tag_condition(tag):   retorna true se a tag pode ser propagada
 *                       diretamente sem descer (ex: mx2 < v <= mx).
 */

/* --- Exemplo de NODE e TAG (chmin em range + query de soma/max) ---
struct Tag {
    ll val = LLONG_MAX; // identidade: não faz nada
    void inline compose(const Tag& t) {
        val = min(val, t.val);
    }
};

struct Node {
    ll sum, mx, mx2;
    int cnt_mx, sz;

    Node() : sum(0), mx(LLONG_MIN), mx2(LLONG_MIN), cnt_mx(0), sz(0) {}
    Node(ll v) : sum(v), mx(v), mx2(LLONG_MIN), cnt_mx(1), sz(1) {}

    static inline Node merge(const Node& l, const Node& r) {
        Node res;
        res.sz = l.sz + r.sz;
        res.sum = l.sum + r.sum;
        if (l.mx == r.mx) {
            res.mx = l.mx; res.cnt_mx = l.cnt_mx + r.cnt_mx;
            res.mx2 = max(l.mx2, r.mx2);
        } else if (l.mx > r.mx) {
            res.mx = l.mx; res.cnt_mx = l.cnt_mx;
            res.mx2 = max(l.mx2, r.mx);
        } else {
            res.mx = r.mx; res.cnt_mx = r.cnt_mx;
            res.mx2 = max(l.mx, r.mx2);
        }
        return res;
    }

    // aplica a tag quando tag_condition é verdadeiro
    void inline apply(const Tag& t, int l, int r) {
        sum -= (ll)(mx - t.val) * cnt_mx;
        mx = t.val;
    }

    // ignora o update completamente (nó já satisfaz)
    bool inline break_condition(const Tag& t) const {
        return mx <= t.val;
    }

    // pode aplicar a tag diretamente sem descer
    bool inline tag_condition(const Tag& t) const {
        return mx2 < t.val;
    }
};
*/

template<typename NODE, typename TAG>
struct SegTreeBeats {
    int N;
    vector<NODE> seg;
    vector<TAG> lazy;

    explicit SegTreeBeats(int n) : N(n), seg(4 * n), lazy(4 * n) {}

    template<typename T>
    SegTreeBeats(const vector<T>& v) : SegTreeBeats((int)v.size()) {
        build(1, 0, N - 1, v);
    }

    template<typename T>
    void build(int no, int l, int r, const vector<T>& v) {
        if (l == r) {
            seg[no] = NODE(v[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(no << 1, l, m, v);
        build((no << 1) | 1, m + 1, r, v);
        seg[no] = NODE::merge(seg[no << 1], seg[(no << 1) | 1]);
    }

    void push(int no, int l, int r) {
        int m = (l + r) >> 1;
        int e = no << 1, d = e | 1;

        seg[e].apply(lazy[no], l, m);
        lazy[e].compose(lazy[no]);

        seg[d].apply(lazy[no], m + 1, r);
        lazy[d].compose(lazy[no]);

        lazy[no] = TAG();
    }

    void update(int no, int l, int r, int a, int b, const TAG& v) {
        if (b < l || r < a || seg[no].break_condition(v)) return;
        if (a <= l && r <= b && seg[no].tag_condition(v)) {
            seg[no].apply(v, l, r);
            lazy[no].compose(v);
            return;
        }
        push(no, l, r);
        int m = (l + r) >> 1;
        update(no << 1, l, m, a, b, v);
        update((no << 1) | 1, m + 1, r, a, b, v);
        seg[no] = NODE::merge(seg[no << 1], seg[(no << 1) | 1]);
    }

    NODE query(int no, int l, int r, int a, int b) {
        if (b < l || r < a) return NODE();
        if (a <= l && r <= b) return seg[no];
        push(no, l, r);
        int m = (l + r) >> 1;
        return NODE::merge(query(no << 1, l, m, a, b),
                           query((no << 1) | 1, m + 1, r, a, b));
    }

    void update(int l, int r, const TAG& v) { update(1, 0, N - 1, l, r, v); }
    NODE query(int l, int r) { return query(1, 0, N - 1, l, r); }
};
