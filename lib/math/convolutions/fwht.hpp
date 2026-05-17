#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* FWHT — Fast Walsh-Hadamard Transform
 * Complexidade: O(N log N)
 *
 * Convolução bitwise: c[k] = Σ a[i]*b[j] onde i op j = k
 *
 * fwht_conv<'^'>(a, b) → convolução XOR
 * fwht_conv<'|'>(a, b) → convolução OR
 * fwht_conv<'&'>(a, b) → convolução AND
 *
 * Tamanhos são ajustados para a próxima potência de 2 automaticamente.
 */

template<char op>
void fwht(vector<ll>& a, bool inv = false) {
    int n = a.size();
    for (int len = 1; len < n; len *= 2)
        for (int i = 0; i < n; i += 2*len)
            for (int j = 0; j < len; j++) {
                ll u = a[i+j], v = a[i+j+len];
                if (op == '^') a[i+j] = u+v, a[i+j+len] = u-v;
                if (op == '|') a[i+j+len] = v + (inv ? -u : +u);
                if (op == '&') a[i+j]     = u + (inv ? -v : +v);
            }
    if (op == '^' && inv) for (auto& x : a) x /= n;
}

template<char op>
vector<ll> fwht_conv(vector<ll> a, vector<ll> b) {
    int n = 1;
    while (n < (int)max(a.size(), b.size())) n *= 2;
    a.resize(n); b.resize(n);
    fwht<op>(a); fwht<op>(b);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    fwht<op>(a, true);
    return a;
}
