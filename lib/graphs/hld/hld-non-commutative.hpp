#pragma once
#include <bits/stdc++.h>
#include "../../data-structures/segment-tree/segment-tree.hpp"
using namespace std;

/* HLD Não-Comutativo (Update Pontual)
 * Para operacoes onde A * B != B * A.
 * Requisito: DoubleNode para gerenciar merges em ambas as direcoes.
 */

template<typename NODE>
struct DoubleNode {
    NODE down, up; 
    DoubleNode() : down(NODE()), up(NODE()) {}
    DoubleNode(const NODE& n) : down(n), up(n) {}
    DoubleNode(const NODE& d, const NODE& u) : down(d), up(u) {}

    static inline DoubleNode merge(const DoubleNode& l, const DoubleNode& r) {
        return {
            NODE::merge(l.down, r.down),
            NODE::merge(r.up, l.up)
        };
    }
};

template<typename NODE>
struct HLD {
    int n, t;
    vector<int> p, sz, d, head, pos, tour;
    SegTree<DoubleNode<NODE>> st; 

    HLD(const vector<vector<int>>& adj, const vector<NODE>& vals, int root = 0)
     : n(adj.size()), t(0), p(n), sz(n), d(n), head(n), pos(n), tour(n), st(n) {
        
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
            tour[pos[u]] = u;
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

        vector<DoubleNode<NODE>> base(n);
        for(int i = 0; i < n; i++)
            base[pos[i]] = DoubleNode<NODE>(vals[i]);
        st = SegTree<DoubleNode<NODE>>(base);
    }

    void update(int u, const NODE& val) {
        st.update(pos[u], DoubleNode<NODE>(val));
    }

    NODE query_path(int u, int v) {
        NODE L, R;
        while (head[u] != head[v]) {
            if (d[head[u]] > d[head[v]]) {
                L = NODE::merge(L, st.query(pos[head[u]], pos[u]).up);
                u = p[head[u]];
            } else {
                R = NODE::merge(st.query(pos[head[v]], pos[v]).down, R);
                v = p[head[v]];
            }
        }
        if (d[u] > d[v]) L = NODE::merge(L, st.query(pos[v], pos[u]).up);
        else R = NODE::merge(st.query(pos[u], pos[v]).down, R);
        
        return NODE::merge(L, R);
    }

    NODE query_subtree(int u) {
        return st.query(pos[u], pos[u] + sz[u] - 1).down;
    }
};