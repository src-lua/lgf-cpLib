#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* Mo's Algorithm — O((N + Q) * sqrt(N))
 * queries: vetor de {l, r} 0-indexado, fechado.
 * add(i), rem(i): adicionam/removem o elemento i da janela.
 * ans(qi): registra resposta para a query de índice qi.
 *
 * Exemplo:
 *   vector<int> ans(q);
 *   Mo mo(n, queries);
 *   mo.run(
 *       [&](int i) { ... },
 *       [&](int i) { ... },
 *       [&](int qi) { ans[qi] = ...; }
 *   );
 */

struct Mo {
  int n, block;
  struct Query {
    int l, r, idx;
  };
  vector<Query> queries;

  Mo(int n, vector<pair<int, int>> &qs)
      : n(n), block(max(1, (int)sqrt(n))) {
    for (int i = 0; i < (int)qs.size(); i++)
      queries.push_back({qs[i].first, qs[i].second, i});
    sort(queries.begin(), queries.end(),
         [&](const Query &a, const Query &b) {
           int ba = a.l / block, bb = b.l / block;
           if (ba != bb) return ba < bb;
           return (ba & 1) ? a.r > b.r : a.r < b.r;
         });
  }

  template <typename Add, typename Rem, typename Ans>
  void run(Add add, Rem rem, Ans ans) {
    int cur_l = 0, cur_r = -1;
    for (auto &[l, r, idx] : queries) {
      while (cur_r < r) add(++cur_r);
      while (cur_l > l) add(--cur_l);
      while (cur_r > r) rem(cur_r--);
      while (cur_l < l) rem(cur_l++);
      ans(idx);
    }
  }
};

/* HilbertMo — Mo com ordenação pela curva de Hilbert
 * Mesma interface que Mo, mas com constante menor na prática.
 */

struct HilbertMo {
  struct Query {
    int l, r, idx;
    ll ord;
  };
  vector<Query> queries;

  static ll hilbert(int x, int y, int n) {
    ll d = 0;
    for (int s = n >> 1; s; s >>= 1) {
      int rx = (x & s) > 0, ry = (y & s) > 0;
      d += (ll)s * s * ((3 * rx) ^ ry);
      if (!ry) {
        if (rx) {
          x = s - 1 - x;
          y = s - 1 - y;
        }
        swap(x, y);
      }
    }
    return d;
  }

  HilbertMo(int n, vector<pair<int, int>> &qs) {
    int hn = 1;
    while (hn < n) hn <<= 1;
    for (int i = 0; i < (int)qs.size(); i++)
      queries.push_back(
        {qs[i].first, qs[i].second, i,
         hilbert(qs[i].first, qs[i].second, hn)});
    sort(queries.begin(), queries.end(),
         [](const Query &a, const Query &b) {
           return a.ord < b.ord;
         });
  }

  template <typename Add, typename Rem, typename Ans>
  void run(Add add, Rem rem, Ans ans) {
    int cur_l = 0, cur_r = -1;
    for (auto &[l, r, idx, ord] : queries) {
      while (cur_r < r) add(++cur_r);
      while (cur_l > l) add(--cur_l);
      while (cur_r > r) rem(cur_r--);
      while (cur_l < l) rem(cur_l++);
      ans(idx);
    }
  }
};
