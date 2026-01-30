#pragma once
#include <bits/stdc++.h>
#include "../../data-structures/segment-tree/lazy-segment-tree.hpp"
using namespace std;

/* HLD Comutativo com Lazy Propagation
 * Para operacoes onde A + B = B + A.
 * Permite updates e queries em caminhos e subarvores.
 * Requisito: data-structures/segment-tree/lazy-segment-tree.hpp
 */

template<typename NODE, typename TAG>
struct HLD {
    int n, t;
    vector<int> p, sz, d, head, pos;
    LazySegmentTree<NODE, TAG> st; 

    HLD(const vector<vector<int>>& adj, const vector<NODE>& vals, int root = 0)
        : n(adj.size()), t(0), p(n), sz(n), d(n), head(n), pos(n), st(n) {

        vector<vector<int>> g = adj;
        d[root] = 0, p[root] = root;

        auto dfs_sz = [&](auto self, int u) -> void {
            sz[u] = 1;
            int best_v = -1, max_sz = -1;
            for (auto &v : g[u]) {
                if (v == p[u]) continue;
                d[v] = d[u] + 1; p[v] = u;
                self(self, v);
                sz[u] += sz[v];
                if (sz[v] > max_sz) { max_sz = sz[v]; best_v = v; }
            }
            if (best_v != -1) {
                for (int i = 0; i < (int)g[u].size(); i++) {
                    if (g[u][i] == best_v && i != 0) {
                        swap(g[u][0], g[u][i]);
                        break;
                    }
                }
            }
        };

        auto dfs_hld = [&](auto self, int u) -> void {
            pos[u] = t++;
            for (int i = 0; i < (int)g[u].size(); i++) {
                int v = g[u][i];
                if (v == p[u]) continue;
                head[v] = (i == 0 ? head[u] : v);
                self(self, v);
            }
        };

        dfs_sz(dfs_sz, root);
        head[root] = root;
        dfs_hld(dfs_hld, root);

        vector<NODE> base(n);
        for(int i = 0; i < n; i++)
            base[pos[i]] = vals[i];
        st = LazySegmentTree<NODE, TAG>(base);
    }

    void update_path(int u, int v, const TAG& tag) {
        while (head[u] != head[v]) {
            if (d[head[u]] > d[head[v]]) swap(u, v);
            st.update(pos[head[v]], pos[v], tag);
            v = p[head[v]];
        }
        if (d[u] > d[v]) swap(u, v);
        st.update(pos[u], pos[v], tag);
    }

    NODE query_path(int u, int v) {
        NODE res;
        while (head[u] != head[v]) {
            if (d[head[u]] > d[head[v]]) swap(u, v);
            res = NODE::merge(res, st.query(pos[head[v]], pos[v]));
            v = p[head[v]];
        }
        if (d[u] > d[v]) swap(u, v);
        return NODE::merge(res, st.query(pos[u], pos[v]));
    }

    void update_subtree(int u, const TAG& tag) {
        st.update(pos[u], pos[u] + sz[u] - 1, tag);
    }

    NODE query_subtree(int u) {
        return st.query(pos[u], pos[u] + sz[u] - 1);
    }
};