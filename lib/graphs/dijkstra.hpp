#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Dijkstra — Caminho mínimo de fonte única
 * Complexidade: O((V + E) log V)
 * Requer pesos não-negativos.
 *
 * adj[u] = lista de {v, w}: aresta u→v com peso w
 *
 * Retorna vetor dist onde dist[v] = distância mínima de s a v.
 * dist[v] = INF se v é inalcançável.
 */

template<typename T>
vector<T> dijkstra(const vector<vector<pair<int,T>>>& adj, int s) {
    int n = adj.size();
    const T INF = numeric_limits<T>::max();
    vector<T> dist(n, INF);
    priority_queue<pair<T,int>, vector<pair<T,int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }
    return dist;
}
