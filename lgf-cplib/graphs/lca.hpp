#pragma once
#include <bits/stdc++.h>
#include "../data-structures/sparse-table/sparse-table.hpp"
using namespace std;

/* LCA (Lowest Common Ancestor) via RMQ
 * Encontra o ancestral comum mais próximo de dois vértices em uma árvore.
 * Complexidade: O(N log N) no build, O(1) por query.
 * Memória: O(N log N)
 * Requisitos:
 * - Grafo deve ser uma árvore (conexo e acíclico).
 * - Dependência: sparse-table/sparse-table.hpp
 * Métodos:
 * - lca(u, v): Retorna o LCA de u e v.
 * - dist(u, v): Retorna a distância entre u e v.
 * - is_ancestor(u, v): Verifica se u é ancestral de v.
 * - parent(u): Retorna o pai de u.
 */

struct LCANode {
    int dep, id;
    LCANode(int d = 1e9, int pos = -1) : dep(d), id(pos) {}
    
    static inline LCANode merge(const LCANode& l, const LCANode& r) {
        return l.dep < r.dep ? l : r;
    }
};

struct LCA {
    int N;
    vector<int> first, tour, d, p;
    SparseTable<LCANode> st;

    LCA(int n, int root, const vector<vector<int>>& adj) 
        : N(n), first(n), d(n), p(n, -1), st(vector<LCANode>()) {
        
        vector<int> tour_depths;
        tour.reserve(2 * n);
        tour_depths.reserve(2 * n);

        auto dfs = [&](auto self, int u, int parent_id, int dep) -> void {
            p[u] = parent_id;
            d[u] = dep;
            first[u] = tour.size();
            tour.push_back(u);
            tour_depths.push_back(dep);
            for (int v : adj[u]) {
                if (v == parent_id) continue;
                self(self, v, u, dep + 1);
                tour.push_back(u);
                tour_depths.push_back(dep);
            }
        };

        dfs(dfs, root, -1, 0);
        st = SparseTable<LCANode>(tour_depths);
    }

    int parent(int u) {
        return p[u];
    }

    int lca(int u, int v) {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        return tour[st.query(l, r).id];
    }

    int dist(int u, int v) {
        return d[u] + d[v] - 2 * d[lca(u, v)];
    }

    bool is_ancestor(int u, int v) {
        return lca(u, v) == u;
    }
};