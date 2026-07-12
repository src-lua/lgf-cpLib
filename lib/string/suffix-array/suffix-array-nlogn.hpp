#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Suffix Array O(N log N) — Prefix Doubling com Count Sort
 * sa[i]  = índice do i-ésimo sufixo em ordem lexicográfica.
 * rk[i]  = rank do sufixo s[i..] (inverso de sa).
 * lcp[i] = LCP entre sa[i-1] e sa[i] (lcp[0] = 0).
 * Adiciona '$' ao final da string internamente.
 * Complexidade: O(N log N) build, O(|P| log N) search.
 *
 * Aplicações:
 * - Busca de padrão P: search(p) retorna [lo, hi) no SA.
 * - Substring mais longa repetida: *max_element(lcp).
 * - Número de substrings distintas: N*(N+1)/2 - sum(lcp).
 * - LCS de duas strings: SuffixArray::lcs(s, t).
 */

struct SuffixArray {
  string s;
  vector<int> sa, rk, lcp;

  SuffixArray() {}

  SuffixArray(string s) : s(s) {
    build();
    build_lcp();
  }

  void build() {
    s += '$';
    int n = s.size();
    sa.resize(n);
    rk.resize(n);

    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) sa[i] = a[i].second;
    rk[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      int inc = a[i].first != a[i - 1].first;
      rk[sa[i]] = rk[sa[i - 1]] + inc;
    }

    for (int k = 0; (1 << k) < n; k++) {
      for (int i = 0; i < n; i++)
        sa[i] = (sa[i] - (1 << k) + n) % n;
      count_sort();
      vector<int> new_rk(n);
      new_rk[sa[0]] = 0;
      auto snd = [&](int x) { return rk[(x + (1 << k)) % n]; };
      for (int i = 1; i < n; i++) {
        pair<int, int> prev = {rk[sa[i - 1]], snd(sa[i - 1])};
        pair<int, int> now = {rk[sa[i]], snd(sa[i])};
        new_rk[sa[i]] = new_rk[sa[i - 1]] + (now != prev);
      }
      rk = new_rk;
    }
  }

  void count_sort() {
    int n = sa.size();
    vector<int> new_sa(n), cnt(n, 0), pos(n, 0);
    for (auto e : rk) cnt[e]++;
    for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
    for (auto e : sa) new_sa[pos[rk[e]]++] = e;
    sa = new_sa;
  }

  void build_lcp() {
    int n = sa.size();
    lcp.assign(n, 0);
    for (int i = 0, h = 0; i < n; i++) {
      if (rk[i] == 0) {
        h = 0;
        continue;
      }
      int j = sa[rk[i] - 1];
      while (s[i + h] == s[j + h]) h++;
      lcp[rk[i]] = h;
      if (h) h--;
    }
  }

  // Intervalo [lo, hi) no SA onde p ocorre.
  pair<int, int> search(const string &p) const {
    int lo, hi, n = sa.size();
    {
      int l = 0, r = n;
      while (l < r) {
        int m = (l + r) / 2;
        if (s.compare(sa[m], p.size(), p) < 0) l = m + 1;
        else r = m;
      }
      lo = l;
    }
    {
      int l = 0, r = n;
      while (l < r) {
        int m = (l + r) / 2;
        if (s.compare(sa[m], p.size(), p) <= 0) l = m + 1;
        else r = m;
      }
      hi = l;
    }
    return {lo, hi};
  }

  // LCS; sep deve diferir de '$' e não aparecer em a ou b.
  static string lcs(const string &a, const string &b,
                    char sep = 1) {
    SuffixArray suf(a + sep + b);
    int m = a.size(), best = 0, pos = 0;
    for (int i = 1; i < (int)suf.sa.size(); i++) {
      bool in_a = suf.sa[i] < m;
      bool prev_in_a = suf.sa[i - 1] < m;
      if (in_a != prev_in_a && suf.lcp[i] > best) {
        best = suf.lcp[i];
        pos = suf.sa[i];
      }
    }
    return suf.s.substr(pos, best);
  }
};
