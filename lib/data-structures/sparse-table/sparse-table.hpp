#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Sparse Table (Static RMQ)
 * Realiza consultas em range em tempo constante.
 * Complexidade: O(N log N) no build, O(1) na query.
 * Memória: O(N log N)
 * Requisitos:
 * - NODE deve ter: static merge(const NODE&, const NODE&) e construtor.
 * - A operação DEVE ser idempotente: f(a, a) = a.
 */

/* --- Exemplo de NODE (Indice do Minimo) ---
struct Node {
    int val, pos;
    Node(int v = 2e9, int p = -1) : val(v), pos(p) {}
    
    static inline Node merge(const Node& l, const Node& r) {
        if (l.val <= r.val) return l;
        return r;
    }
};
*/

template<typename NODE>
struct SparseTable {
    int N, K;
    vector<vector<NODE>> st;
    vector<int> lg;

    template<typename T>
    SparseTable(const vector<T>& v) : N(v.size()) {
        K = (N > 0) ? __lg(N) : 0;
        st.assign(K + 1, vector<NODE>(N));
        lg.assign(N + 1, 0);
        for (int i = 2; i <= N; i++) lg[i] = lg[i / 2] + 1;
        for (int i = 0; i < N; i++) st[0][i] = NODE(v[i], i);
        for (int j = 1; j <= K; j++)
            for (int i = 0; i + (1 << j) <= N; i++)
                st[j][i] = NODE::merge(st[j - 1][i],
                                       st[j - 1][i + (1 << (j - 1))]);
    }

    NODE query(int l, int r) {
        int j = lg[r - l + 1];
        return NODE::merge(st[j][l], st[j][r - (1 << j) + 1]);
    }
};