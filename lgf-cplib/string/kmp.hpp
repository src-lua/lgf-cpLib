#pragma once
#include <bits/stdc++.h>
using namespace std;

/* KMP (Knuth-Morris-Pratt)
 * failure[i] = tamanho do maior prefixo próprio de s[0..i] que é também sufixo.
 * Complexidade: O(N) build, O(N + M) busca.
 *
 * Aplicações:
 * - Busca de padrão P em texto T em O(|P| + |T|).
 * - Menor período da string: N - failure[N-1].
 * - Contar ocorrências de todos os prefixos como sufixos.
 */

vector<int> kmp_failure(const string& s) {
    int n = s.size();
    vector<int> f(n, 0);
    for (int i = 1; i < n; i++) {
        int j = f[i - 1];
        while (j > 0 && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) j++;
        f[i] = j;
    }
    return f;
}

// Busca todas as ocorrências de pattern em text. Retorna índices (0-indexed).
vector<int> kmp_search(const string& pattern, const string& text) {
    string s = pattern + "$" + text;
    vector<int> f = kmp_failure(s);
    int p = pattern.size();
    vector<int> res;
    for (int i = p + 1; i < (int)s.size(); i++)
        if (f[i] == p) res.push_back(i - 2 * p - 1);
    return res;
}
