#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Z-Function
 * z[i] = tamanho do maior prefixo de s que coincide com s[i..].
 * z[0] = 0 por convenção.
 * Complexidade: O(N) build.
 *
 * Aplicações:
 * - Busca de padrão P em texto T: z-function de P + "$" + T.
 *   Posições i onde z[i] == |P| são ocorrências de P em T.
 * - Contar ocorrências de prefixo de tamanho k: contar z[i] >= k.
 * - Menor período da string: menor p tal que p divide N e z[p] == N - p.
 */

vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// Busca todas as ocorrências de pattern em text. Retorna índices (0-indexed).
vector<int> z_search(const string& pattern, const string& text) {
    string s = pattern + "$" + text;
    vector<int> z = z_function(s);
    int p = pattern.size();
    vector<int> res;
    for (int i = p + 1; i < (int)s.size(); i++)
        if (z[i] == p) res.push_back(i - p - 1);
    return res;
}
