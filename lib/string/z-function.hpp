#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Z-Function
 * z[i] = maior prefixo de s que coincide com s[i..].
 * z[0] = 0 por convenção.
 * Complexidade: O(N) build.
 *
 * Aplicações:
 * - Busca P em T: calcule Z de P + "$" + T.
 * - Ocorrências de prefixo k: conte z[i] >= k.
 * - Menor período: menor p | N com z[p] == N-p.
 */

vector<int> z_function(const string &s) {
  int n = s.size();
  vector<int> z(n, 0);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}

// Índices de todas as ocorrências de pattern em text.
vector<int> z_search(const string &pattern, const string &text) {
  string s = pattern + "$" + text;
  vector<int> z = z_function(s);
  int p = pattern.size();
  vector<int> positions;
  for (int i = p + 1; i < (int)s.size(); i++)
    if (z[i] == p) positions.push_back(i - p - 1);
  return positions;
}
