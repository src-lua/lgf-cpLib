#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Disjoint Sparse Table (Static Range Query)
 * Realiza consultas em range em O(1) para qualquer operação associativa.
 * Complexidade: O(N log N) no build, O(1) na query.
 * Memória: O(N log N)
 * Requisitos:
 * - NODE deve ter: static merge(const NODE&, const NODE&) e construtor.
 * - Operação deve ser ASSOCIATIVA: f(f(a,b),c) = f(a,f(b,c)).
 */

/* --- Exemplo de NODE (Soma em Range) ---
struct Node {
    ll val;
    Node(ll v = 0) : val(v) {}
    static inline Node merge(const Node& l, const Node& r) {
        return Node(l.val + r.val);
    }
};
*/

template<typename NODE>
struct DisjointSparseTable {
    int N, K;
    vector<vector<NODE>> st;

    template<typename T>
    DisjointSparseTable(const vector<T>& v) : N(v.size()) {
        if (N == 0) return;
        K = __lg(2 * N - 1);
        st.assign(K, vector<NODE>(1 << K));

        for (int i = 0; i < N; i++) st[0][i] = NODE(v[i]);

        for (int j = 1; j < K; j++) {
            int len = 1 << j;
            for (int m = len; m <= (1 << K); m += 2 * len) {
                if (m < N) st[j][m] = st[0][m];
                for (int i = m + 1; i < min(N, m + len); i++)
                    st[j][i] = NODE::merge(st[j][i - 1], st[0][i]);
                
                if (m - 1 < N) st[j][m - 1] = st[0][m - 1];
                for (int i = m - 2; i >= m - len; i--)
                    st[j][i] = NODE::merge(st[0][i], st[j][i + 1]);
            }
        }
    }

    inline NODE query(int l, int r) {
        if (l == r) return st[0][l];
        int j = __lg(l ^ r);
        return NODE::merge(st[j][l], st[j][r]);
    }
};