#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Busca unimodal — f deve ser unimodal no intervalo dado.
 *
 * ternary_min/max(lo, hi, f)          → inteiros, O(log N)
 * golden_min/max(lo, hi, f, iters=200) → contínuo, O(iters); 200 iters ≈ 1e-30
 */

// Ternary search para mínimo em inteiros [lo, hi]
template<typename F>
long long ternary_min(long long lo, long long hi, F f) {
    while (hi - lo > 2) {
        long long m1 = lo + (hi - lo) / 3;
        long long m2 = hi - (hi - lo) / 3;
        if (f(m1) <= f(m2)) hi = m2;
        else                lo = m1;
    }
    long long best = lo;
    for (long long x = lo + 1; x <= hi; x++)
        if (f(x) < f(best)) best = x;
    return best;
}

// Ternary search para máximo em inteiros [lo, hi]
template<typename F>
long long ternary_max(long long lo, long long hi, F f) {
    while (hi - lo > 2) {
        long long m1 = lo + (hi - lo) / 3;
        long long m2 = hi - (hi - lo) / 3;
        if (f(m1) >= f(m2)) hi = m2;
        else                lo = m1;
    }
    long long best = lo;
    for (long long x = lo + 1; x <= hi; x++)
        if (f(x) > f(best)) best = x;
    return best;
}

// Golden section search para mínimo em contínuo [lo, hi]
template<typename F>
double golden_min(double lo, double hi, F f, int iters = 200) {
    const double phi = (sqrt(5.0) - 1.0) / 2.0;  // ≈ 0.618
    double m1 = hi - phi * (hi - lo);
    double m2 = lo + phi * (hi - lo);
    double f1 = f(m1), f2 = f(m2);
    for (int i = 0; i < iters; i++) {
        if (f1 < f2) {
            hi = m2; m2 = m1; f2 = f1;
            m1 = hi - phi * (hi - lo); f1 = f(m1);
        } else {
            lo = m1; m1 = m2; f1 = f2;
            m2 = lo + phi * (hi - lo); f2 = f(m2);
        }
    }
    return (lo + hi) / 2.0;
}

// Golden section search para máximo em contínuo [lo, hi]
template<typename F>
double golden_max(double lo, double hi, F f, int iters = 200) {
    return golden_min(lo, hi, [&](double x) { return -f(x); }, iters);
}
