#pragma once
#include "point.hpp"
using namespace std;

/* Closest Pair — Par de pontos mais próximos
 * Complexidade: O(N log N)
 *
 * closest_pair(pts) → índices {i, j} do par; i < j.
 *
 * Distância ao quadrado: (pts[i] - pts[j]).dist2()
 * Funciona com coordenadas inteiras, sem erro de precisão.
 */

template <typename T>
pair<int, int> closest_pair(const vector<Point<T>> &pts) {
  int n = pts.size();
  vector<int> idx(n);
  iota(idx.begin(), idx.end(), 0);
  sort(idx.begin(), idx.end(),
       [&](int a, int b) { return pts[a].x < pts[b].x; });

  T best = (pts[idx[0]] - pts[idx[1]]).dist2();
  pair<int, int> ans = {idx[0], idx[1]};

  // set ordenado por (y, índice)
  set<pair<T, int>> active;
  for (int l = 0, r = 0; r < n; r++) {
    const Point<T> &pr = pts[idx[r]];
    T delta = (T)ceil(sqrt((double)best)) + 1;
    while (pr.x - pts[idx[l]].x > delta) {
      active.erase({pts[idx[l]].y, idx[l]});
      l++;
      delta = (T)ceil(sqrt((double)best)) + 1;
    }
    auto lo = active.lower_bound({pr.y - delta, INT_MIN});
    auto hi = active.upper_bound({pr.y + delta, INT_MAX});
    for (auto it = lo; it != hi; it++) {
      T d = (pr - pts[it->second]).dist2();
      if (d < best) {
        best = d;
        ans = {idx[r], it->second};
      }
    }
    active.insert({pr.y, idx[r]});
  }
  if (ans.first > ans.second) swap(ans.first, ans.second);
  return ans;
}
