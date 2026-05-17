#pragma once
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = double;

const ld eps = 1e-9;
bool eq(ll a, ll b) { return a == b; }
bool eq(ld a, ld b) { return abs(a - b) <= eps; }

template<typename T>
struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    bool operator<(Point o)  const { return tie(x, y) < tie(o.x, o.y); }
    bool operator==(Point o) const { return eq(x, o.x) && eq(y, o.y); }
    bool operator!=(Point o) const { return !(*this == o); }

    Point operator+(Point o) const { return {x + o.x, y + o.y}; }
    Point operator-(Point o) const { return {x - o.x, y - o.y}; }
    Point operator*(T k)     const { return {x * k, y * k}; }
    Point operator/(T k)     const { return {x / k, y / k}; }

    T dot(Point o)   const { return x * o.x + y * o.y; }
    T cross(Point o) const { return x * o.y - y * o.x; }
    // área com sinal do triângulo (this, a, b)
    T cross(Point a, Point b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }

    ld len()         const { return hypot((ld)x, (ld)y); }
    Point<ld> norm() const { ld l = len(); return {x / l, y / l}; }
    Point perp()     const { return {-y, x}; }  // rotação 90° CCW
    Point<ld> rotate(ld a) const { // a em radianos
        return {x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)};
    }

    friend ostream& operator<<(ostream& os, Point p) {
        return os << p.x << " " << p.y;
    }
};

using Pt  = Point<ll>;
using Ptd = Point<ld>;

// ângulo entre os vetores p e q
template<typename T>
ld angle(Point<T> p, Point<T> q) { return atan2((ld)p.cross(q), (ld)p.dot(q)); }

// área com sinal do triângulo (p, q, r) — positivo = CCW
template<typename T>
T sarea(Point<T> p, Point<T> q, Point<T> r) { return p.cross(q, r); }

// se p, q, r são colineares
template<typename T>
bool is_collinear(Point<T> p, Point<T> q, Point<T> r) {
    return eq(sarea(p, q, r), (T)0);
}
