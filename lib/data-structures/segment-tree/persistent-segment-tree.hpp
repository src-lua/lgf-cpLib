#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Persistent Segment Tree (Point Update, Range Query)
 * Permite consultas em versões anteriores da árvore.
 * Complexidade: O(log N) por update e query.
 * Memória: O(Q log N) onde Q é o número de updates.
 * Requisitos:
 * - NODE deve ter: static merge(const NODE&, const NODE&) e construtor identidade.
 */

/* --- Exemplo de NODE (Soma) ---
struct Node {
    int val;
    Node(int v = 0) : val(v) {}
    static inline Node merge(const Node& l, const Node& r) {
        return Node(l.val + r.val);
    }
};
*/

template<typename NODE>
struct PersistentSegmentTree {
    struct InternalNode {
        NODE data;
        int l, r;
        InternalNode() : data(NODE()), l(0), r(0) {}
    };

    int N;
    vector<InternalNode> st;
    vector<int> roots;

    PersistentSegmentTree(int n) : N(n) {
        st.emplace_back(); // Nó 0 é o nó nulo
        roots.push_back(build(0, N - 1));
    }

    int build(int L, int R) {
        int node = st.size();
        st.emplace_back();
        if (L == R) return node;
        int mid = (L + R) / 2;
        st[node].l = build(L, mid);
        st[node].r = build(mid + 1, R);
        st[node].data = NODE::merge(st[st[node].l].data, st[st[node].r].data);
        return node;
    }

    // Retorna o índice da nova raiz após o update
    int update(int prev_root, int L, int R, int idx, NODE v) {
        int node = st.size();
        st.push_back(st[prev_root]); 
        if (L == R) {
            st[node].data = v; // Ou NODE::merge se for incremental
            return node;
        }
        int mid = (L + R) / 2;
        if (idx <= mid) st[node].l = update(st[prev_root].l, L, mid, idx, v);
        else st[node].r = update(st[prev_root].r, mid + 1, R, idx, v);
        
        st[node].data = NODE::merge(st[st[node].l].data, st[st[node].r].data);
        return node;
    }

    NODE query(int node, int L, int R, int i, int j) {
        if (i > R || j < L) return NODE();
        if (i <= L && R <= j) return st[node].data;
        int mid = (L + R) / 2;
        return NODE::merge(query(st[node].l, L, mid, i, j),
                           query(st[node].r, mid + 1, R, i, j));
    }

    void update(int idx, NODE v) {
        roots.push_back(update(roots.back(), 0, N - 1, idx, v));
    }
    
    NODE query(int version, int l, int r) { return query(roots[version], 0, N - 1, l, r); }
};