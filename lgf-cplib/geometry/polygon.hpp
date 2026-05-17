#pragma once
#include "line.hpp"
using namespace std;

// 2x a área com sinal (>0 = CCW)
template<typename T>
T area2(const vector<Point<T>>& poly) {
    T a = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
        a += poly[i].cross(poly[(i + 1) % n]);
    return a;
}

// área do polígono
template<typename T>
ld polarea(const vector<Point<T>>& poly) {
    return abs((ld)area2(poly)) / 2.0;
}


// 0 = fora, 1 = dentro, 2 = na borda
// O(n), funciona para qualquer polígono simples (convexo ou côncavo)
template<typename T>
int winding(const vector<Point<T>>& poly, Point<T> p) {
    int n = poly.size(), w = 0;
    for (int i = 0; i < n; i++) {
        Point<T> a = poly[i] - p, b = poly[(i+1)%n] - p;
        if (a.y <= 0 && b.y > 0) {
            T c = a.cross(b);
            if (c > 0) w++;
            else if (c == 0) return 2;
        } else if (b.y <= 0 && a.y > 0) {
            T c = a.cross(b);
            if (c < 0) w--;
            else if (c == 0) return 2;
        } else if (b.y == 0 && a.y == 0) {
            if (min(a.x, b.x) <= 0 && 0 <= max(a.x, b.x)) return 2;
        }
    }
    return w != 0 ? 1 : 0;
}

// ponto no interior do casco convexo (CCW, sem colineares), O(log n)
template<typename T>
bool inside_hull(const vector<Point<T>>& hull, Point<T> p) {
    int n = hull.size();
    if (n == 1) return p == hull[0];
    if (n == 2) return hull[0].cross(hull[1], p) == 0
                    && (p - hull[0]).dot(hull[1] - hull[0]) >= 0
                    && (p - hull[1]).dot(hull[0] - hull[1]) >= 0;
    if (hull[0].cross(hull[1], p) <= 0 ||
        hull[0].cross(hull[n-1], p) >= 0) return false;
    int lo = 1, hi = n - 1;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (hull[0].cross(hull[mid], p) > 0) lo = mid;
        else hi = mid;
    }
    return hull[lo].cross(hull[lo+1], p) >= 0;
}

// corta o polígono com a reta r, mantendo pontos p tais que (r.p, r.q, p) é CCW
vector<Ptd> cut_polygon(vector<Ptd> poly, Line r) {
    vector<Ptd> ret;
    int n = poly.size();
    auto ccw = [&](Ptd a, Ptd b, Ptd c) { return (b - a).cross(c - a) > eps; };
    for (int i = 0; i < n; i++) {
        if (ccw(r.p, r.q, poly[i])) ret.push_back(poly[i]);
        if (n == 1) continue;
        Line s(poly[i], poly[(i + 1) % n]);
        Ptd p = inter(r, s);
        if (isinseg(p, s)) ret.push_back(p);
    }
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    if (ret.size() > 1 && ret.back() == ret[0]) ret.pop_back();
    return ret;
}

// se dois polígonos se intersectam — O(n*m)
bool interpol(const vector<Ptd>& v1, const vector<Ptd>& v2) {
    int n = v1.size(), m = v2.size();
    for (auto& p : v1) if (winding(v2, p)) return true;
    for (auto& p : v2) if (winding(v1, p)) return true;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (interseg(Line(v1[i], v1[(i+1)%n]),
                         Line(v2[j], v2[(j+1)%m]))) return true;
    return false;
}

// distância entre dois polígonos
ld distpol(const vector<Ptd>& v1, const vector<Ptd>& v2) {
    if (interpol(v1, v2)) return 0;
    int n = v1.size(), m = v2.size();
    ld ret = 1e18;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ret = min(ret, distseg(Line(v1[i], v1[(i+1)%n]),
                                   Line(v2[j], v2[(j+1)%m])));
    return ret;
}
