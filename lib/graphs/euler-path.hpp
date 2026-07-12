#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Caminho/Circuito Euleriano — Hierholzer — O(V + E)
 *
 * Condições de existência:
 *   Grafo não-direcionado:
 *     - Circuito: todos os vértices com grau par.
 *     - Caminho:  exatamente 2 vértices com grau ímpar (início e fim).
 *   Grafo direcionado:
 *     - Circuito: in_degree[v] == out_degree[v] para todo v.
 *     - Caminho:  exatamente 1 vértice com out-in=+1 (início),
 *                 exatamente 1 com in-out=+1 (fim), resto iguais.
 *
 * euler(adj, s) → vetor de vértices do caminho (tamanho E+1).
 *   Retorna vetor vazio se não existe caminho euleriano a partir de s.
 *   adj[u] = lista de {v, edge_id}: aresta u→v com índice edge_id.
 *   Para grafo não-direcionado, adicione cada aresta em ambas as direções
 *   com o mesmo edge_id; o algoritmo marca arestas visitadas pelo id.
 */

vector<int> euler(vector<vector<pair<int,int>>>& adj, int s) {
    int E = 0;
    for (auto& v : adj) E += v.size();
    E /= 2; // para não-direcionado; para direcionado, remova o /2

    vector<bool> used_edge(E, false);
    vector<int> ptr(adj.size(), 0);
    vector<int> path, stk = {s};

    while (!stk.empty()) {
        int v = stk.back();
        bool found = false;
        while (ptr[v] < (int)adj[v].size()) {
            auto [u, eid] = adj[v][ptr[v]++];
            if (!used_edge[eid]) {
                used_edge[eid] = true;
                stk.push_back(u);
                found = true;
                break;
            }
        }
        if (!found) {
            path.push_back(v);
            stk.pop_back();
        }
    }

    if ((int)path.size() != E + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}
