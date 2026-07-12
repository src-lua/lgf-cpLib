#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Manacher's Algorithm (Palindrome Detection)
 * Encontra todos os palíndromos em tempo linear.
 * Complexidade: O(N) onde N é o tamanho da string.
 * Memória: O(N)
 * Funções:
 * - manacher(s): maior palíndromo centrado em i.
 * - palindrome: testa s[i..j] em O(1).
 * - pal_begin(s): maior palíndromo começando em i.
 * - pal_end(s): maior palíndromo terminando em i.
 */

template <typename T>
vector<int> manacher(const T &s) {
  int l = 0, r = -1, n = s.size();
  vector<int> d1(n), d2(n);
  for (int i = 0; i < n; i++) {
    int k = i > r ? 1 : min(d1[l + r - i], r - i);
    while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) k++;
    d1[i] = k--;
    if (i + k > r) l = i - k, r = i + k;
  }
  l = 0, r = -1;
  for (int i = 0; i < n; i++) {
    int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
    k++;
    while (i + k <= n && i - k >= 0 && s[i + k - 1] == s[i - k])
      k++;
    d2[i] = --k;
    if (i + k - 1 > r) l = i - k, r = i + k - 1;
  }
  vector<int> res(2 * n - 1);
  for (int i = 0; i < n; i++) res[2 * i] = 2 * d1[i] - 1;
  for (int i = 0; i < n - 1; i++)
    res[2 * i + 1] = 2 * d2[i + 1];
  return res;
}

template <typename T>
struct palindrome {
  vector<int> man;

  palindrome(const T &s) : man(manacher(s)) {}

  bool query(int i, int j) { return man[i + j] >= j - i + 1; }
};

template <typename T>
vector<int> pal_begin(const T &s) {
  int n = s.size() - 1;
  vector<int> res(s.size());
  palindrome<T> p(s);
  res[n] = 1;
  for (int i = n - 1; i >= 0; i--) {
    res[i] = min(res[i + 1] + 2, n - i + 1);
    while (!p.query(i, i + res[i] - 1)) res[i]--;
  }
  return res;
}

template <typename T>
vector<int> pal_end(const T &s) {
  vector<int> res(s.size());
  palindrome<T> p(s);
  res[0] = 1;
  for (int i = 1; i < s.size(); i++) {
    res[i] = min(res[i - 1] + 2, i + 1);
    while (!p.query(i - res[i] + 1, i)) res[i]--;
  }
  return res;
}
