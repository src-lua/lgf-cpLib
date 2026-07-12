#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Suffix Array O(N) — SA-IS (Induced Sorting)
 * Build O(N). Use quando N muito grande justificar o SA-IS.
 *
 * Campos públicos após construção:
 * sa[i] = índice do i-ésimo sufixo em ordem lexicográfica
 *   rk[i]  = rank do sufixo s[i..] (inverso de sa)
 * lcp[i] = tamanho do LCP entre sa[i-1] e sa[i]; lcp[0] = 0
 *
 * Métodos:
 * search(p) → [lo, hi) no SA; hi-lo é o nº de ocorrências
 */

struct SuffixArrayLinear {
  string s;
  vector<int> sa, rk, lcp;

  SuffixArrayLinear() {}

  SuffixArrayLinear(const string &s) : s(s + '$') {
    vector<int> t(this->s.begin(), this->s.end());
    sa = sa_is(t, 256);
    int n = sa.size();
    rk.resize(n);
    for (int i = 0; i < n; i++) rk[sa[i]] = i;
    build_lcp();
  }

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

  void build_lcp() {
    int n = sa.size();
    lcp.assign(n, 0);
    for (int i = 0, h = 0; i < n - 1; i++) {
      int j = sa[rk[i] - 1];
      while (s[i + h] == s[j + h]) h++;
      lcp[rk[i]] = h;
      if (h) h--;
    }
  }

  template <typename T>
  static vector<int> sa_is(const T &s, int sigma) {
    int n = s.size();
    if (n == 1) return {0};
    if (n == 2)
      return s[0] < s[1] ? vector<int>{0, 1} : vector<int>{1, 0};

    vector<bool> t(n);
    t[n - 1] = true;
    for (int i = n - 2; i >= 0; i--)
      t[i] = s[i] < s[i + 1] || (s[i] == s[i + 1] && t[i + 1]);

    auto is_lms = [&](int i) {
      return i > 0 && t[i] && !t[i - 1];
    };

    vector<int> bkt(sigma + 1, 0);
    for (int c : s) bkt[c + 1]++;
    for (int i = 1; i <= sigma; i++) bkt[i] += bkt[i - 1];

    auto induced_sort = [&](const vector<int> &lms) {
      vector<int> sa(n, -1);
      vector<int> b = bkt;
      for (int i = (int)lms.size() - 1; i >= 0; i--)
        sa[--b[s[lms[i]] + 1]] = lms[i];
      b = bkt;
      for (int i = 0; i < n; i++)
        if (sa[i] > 0 && !t[sa[i] - 1])
          sa[b[s[sa[i] - 1]]++] = sa[i] - 1;
      b = bkt;
      for (int i = n - 1; i >= 0; i--)
        if (sa[i] > 0 && t[sa[i] - 1])
          sa[--b[s[sa[i] - 1] + 1]] = sa[i] - 1;
      return sa;
    };

    vector<int> lms;
    for (int i = 0; i < n; i++)
      if (is_lms(i)) lms.push_back(i);
    vector<int> sa = induced_sort(lms);

    vector<int> rank_(n, -1);
    int cls = 0;
    for (int i = 0, prev = -1; i < n; i++) {
      if (!is_lms(sa[i])) continue;
      if (prev != -1) {
        bool diff = false;
        for (int d = 0;; d++) {
          if (s[prev + d] != s[sa[i] + d] ||
              t[prev + d] != t[sa[i] + d]) {
            diff = true;
            break;
          }
          if (d > 0 && (is_lms(prev + d) || is_lms(sa[i] + d)))
            break;
        }
        if (diff) cls++;
      }
      rank_[sa[i]] = cls;
      prev = sa[i];
    }

    vector<int> lms2, rank2;
    for (int i = 0; i < n; i++)
      if (rank_[i] != -1) {
        lms2.push_back(i);
        rank2.push_back(rank_[i]);
      }

    // Há cls+1 classes distintas, numeradas de 0 a cls.
    vector<int> sa2 = sa_is(rank2, cls + 1);
    vector<int> sorted_lms(lms2.size());
    for (int i = 0; i < (int)sa2.size(); i++)
      sorted_lms[i] = lms2[sa2[i]];

    return induced_sort(sorted_lms);
  }
};
