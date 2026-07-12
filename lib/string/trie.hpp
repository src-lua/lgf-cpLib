#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Trie (Prefix Tree)
 * Inserção e busca de strings em O(|s|).
 * Memória: O(N * ALPHA), N = total de caracteres.
 * Alfabeto: [BASE, BASE + ALPHA).
 */

template <int ALPHA = 26, char BASE = 'a'>
struct Trie {
  struct Node {
    int ch[ALPHA];
    int cnt;
    int end;
    Node() : cnt(0), end(0) { fill(ch, ch + ALPHA, -1); }
  };

  vector<Node> t;

  Trie() { t.emplace_back(); }

  void insert(const string &s) {
    int node = 0;
    for (char c : s) {
      int id = c - BASE;
      if (t[node].ch[id] == -1) {
        t[node].ch[id] = t.size();
        t.emplace_back();
      }
      node = t[node].ch[id];
      t[node].cnt++;
    }
    t[node].end++;
  }

  bool search(const string &s) const {
    int node = 0;
    for (char c : s) {
      int id = c - BASE;
      if (t[node].ch[id] == -1) return false;
      node = t[node].ch[id];
    }
    return t[node].end > 0;
  }

  int count_prefix(const string &s) const {
    int node = 0;
    for (char c : s) {
      int id = c - BASE;
      if (t[node].ch[id] == -1) return 0;
      node = t[node].ch[id];
    }
    return t[node].cnt;
  }

  int count(const string &s) const {
    int node = 0;
    for (char c : s) {
      int id = c - BASE;
      if (t[node].ch[id] == -1) return 0;
      node = t[node].ch[id];
    }
    return t[node].end;
  }
};
