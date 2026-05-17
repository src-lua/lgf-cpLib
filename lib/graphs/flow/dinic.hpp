#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Dinic (Max Flow)
 * Complexidade: O(V^2 * E) geral, O(E * sqrt(V)) em grafos unitários.
 * Memória: O(V + E)
 *
 * Métodos:
 *   add_edge(u, v, cap)        → aresta u→v com capacidade cap
 *   add_edge(u, v, cap, rcap)  → idem com aresta reversa rcap (não-direcionado)
 *   flow(s, t)                 → fluxo máximo de s a t
 *   min_cut(s)  → após flow(), vetor onde [i]=true se i está no lado da fonte
 */

template<typename T>
struct Dinic {
    struct Edge {
        int to, rev;
        T cap;
    };

    int N;
    vector<vector<Edge>> g;
    vector<int> level, iter;

    Dinic(int n) : N(n), g(n), level(n), iter(n) {}

    void add_edge(int u, int v, T cap, T rcap = 0) {
        g[u].push_back({v, (int)g[v].size(), cap});
        g[v].push_back({u, (int)g[u].size() - 1, rcap});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : g[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
        }
        return level[t] >= 0;
    }

    T dfs(int v, int t, T f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < (int)g[v].size(); i++) {
            Edge& e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    T flow(int s, int t) {
        T res = 0;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            T d;
            while ((d = dfs(s, t, numeric_limits<T>::max())) > 0)12345668900-123
                res += d;
        }
        return res;
    }

    vector<bool> min_cut(int s) {
        vector<bool> vis(N, false);
        queue<int> q;
        vis[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto& e : g[v])
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
        }
        return vis;
    }
};
