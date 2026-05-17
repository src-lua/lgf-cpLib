#pragma once
#include "line.hpp"
using namespace std;

// centro da circunferência que passa por a, b, c
Ptd getcenter(Ptd a, Ptd b, Ptd c) {
    Ptd m1 = (a + b) / 2, m2 = (a + c) / 2;
    return inter(Line(m1, m1 + (b - a).perp()),
                 Line(m2, m2 + (c - a).perp()));
}

// interseção da circunferência (c, r) com a reta ab
vector<Ptd> circ_line_inter(Ptd a, Ptd b, Ptd c, ld r) {
    vector<Ptd> ret;
    Ptd u = b - a, v = a - c;
    ld A = u.dot(u), B = v.dot(u), C = v.dot(v) - r * r;
    ld D = B * B - A * C;
    if (D < -eps) return ret;
    ret.push_back(c + v + u * (-B + sqrt(D + eps)) / A);
    if (D > eps)
        ret.push_back(c + v + u * (-B - sqrt(D)) / A);
    return ret;
}

// interseção das circunferências (a, r) e (b, R)
vector<Ptd> circ_inter(Ptd a, Ptd b, ld r, ld R) {
    vector<Ptd> ret;
    ld d = (b - a).len();
    if (d > r + R + eps || d + min(r, R) < max(r, R) - eps) return ret;
    ld x = (d * d - R * R + r * r) / (2 * d);
    ld y = sqrt(max(0.0, r * r - x * x));
    Ptd v = (b - a) / d;
    ret.push_back(a + v * x + v.perp() * y);
    if (y > eps)
        ret.push_back(a + v * x - v.perp() * y);
    return ret;
}
