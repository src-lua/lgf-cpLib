#pragma once
#include "point.hpp"
using namespace std;

struct Line {
    Ptd p, q;
    Line() {}
    Line(Ptd p, Ptd q) : p(p), q(q) {}
};

// se p pertence ao segmento r
bool isinseg(Ptd p, Line r) {
    Ptd a = r.p - p, b = r.q - p;
    return eq(a.cross(b), 0) && a.dot(b) < eps;
}

// projeção do ponto p na reta r
Ptd proj(Ptd p, Line r) {
    if (r.p == r.q) return r.p;
    Ptd v = r.q - r.p, u = p - r.p;
    return r.p + v * (u.dot(v) / v.dot(v));
}

// interseção das retas r e s (retorna {INF,INF} se paralelas)
Ptd inter(Line r, Line s) {
    Ptd u = r.q - r.p, v = s.q - s.p, w = s.p - r.p;
    ld d = u.cross(v);
    if (eq(d, 0)) return {1e18, 1e18};
    return r.p + u * (w.cross(v) / d);
}

// se o segmento r intersecta o segmento s
bool interseg(Line r, Line s) {
    if (isinseg(r.p, s) || isinseg(r.q, s) ||
        isinseg(s.p, r) || isinseg(s.q, r)) return true;
    auto ccw = [](Ptd a, Ptd b, Ptd c) {
        return (b - a).cross(c - a) > eps;
    };
    return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) &&
           ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

// distância do ponto p à reta r
ld disttoline(Ptd p, Line r) {
    return abs((r.q - r.p).cross(p - r.p)) / (r.q - r.p).len();
}

// distância do ponto p ao segmento r
ld disttoseg(Ptd p, Line r) {
    if ((r.q - r.p).dot(p - r.p) < 0) return (p - r.p).len();
    if ((r.p - r.q).dot(p - r.q) < 0) return (p - r.q).len();
    return disttoline(p, r);
}

// distância entre dois segmentos
ld distseg(Line a, Line b) {
    if (interseg(a, b)) return 0;
    return min({disttoseg(a.p, b), disttoseg(a.q, b),
                disttoseg(b.p, a), disttoseg(b.q, a)});
}
