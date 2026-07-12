#pragma once
#include "polygon.hpp"
using namespace std;

// Casco convexo CCW, O(N log N); descarta colineares.
template <typename T>
vector<Point<T>> convex_hull(vector<Point<T>> pts) {
  int n = pts.size();
  if (n < 2) return pts;
  sort(pts.begin(), pts.end());
  vector<Point<T>> h;
  h.reserve(2 * n);
  for (int phase = 0; phase < 2; phase++) {
    int start = h.size();
    for (auto &p : pts) {
      while ((int)h.size() >= start + 2) {
        auto a = h[h.size() - 2], b = h.back();
        if ((b - a).cross(p - a) > 0) break;
        h.pop_back();
      }
      h.push_back(p);
    }
    h.pop_back();
    reverse(pts.begin(), pts.end());
  }
  if (h.size() == 2 && h[0] == h[1]) h.pop_back();
  return h;
}

// Operações O(log n) em casco CCW sem colineares.
struct ConvexPol {
  vector<Ptd> pol;

  ConvexPol() {}
  ConvexPol(vector<Ptd> v) : pol(convex_hull(v)) {}

  // se o ponto está dentro do casco — O(log n)
  bool is_inside(Ptd p) {
    int n = pol.size();
    if (n == 0) return false;
    return inside_hull(pol, p);
  }

  // cmp(p, q) indica que p é mais extremo que q.
  int extreme(const function<bool(Ptd, Ptd)> &cmp) {
    int n = pol.size();
    auto extr = [&](int i, bool &cur_dir) {
      cur_dir = cmp(pol[(i + 1) % n], pol[i]);
      return !cur_dir && !cmp(pol[(i + n - 1) % n], pol[i]);
    };
    bool last_dir, cur_dir;
    if (extr(0, last_dir)) return 0;
    int l = 0, r = n;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (extr(m, cur_dir)) return m;
      bool rel_dir = cmp(pol[m], pol[l]);
      if ((!last_dir && cur_dir) ||
          (last_dir == cur_dir && rel_dir == cur_dir)) {
        l = m;
        last_dir = cur_dir;
      } else r = m;
    }
    return l;
  }

  // Índice do ponto com maior produto interno com v — O(log n).
  int max_dot(Ptd v) {
    return extreme(
      [&](Ptd p, Ptd q) { return p.dot(v) > q.dot(v); });
  }

  // Tangentes por p: índices {esquerda, direita} — O(log n).
  pair<int, int> tangents(Ptd p) {
    auto left = [&](Ptd q, Ptd r) {
      return (r - p).cross(q - p) > eps;
    };
    auto right = [&](Ptd q, Ptd r) {
      return (q - p).cross(r - p) > eps;
    };
    return {extreme(left), extreme(right)};
  }
};
