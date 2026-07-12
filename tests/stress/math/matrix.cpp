#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "lib/math/matrix.hpp"

Matrix<ll> naive_pow(Matrix<ll> m, ll k) {
    Matrix<ll> r(m.n); // identidade
    while (k--) r = r * m;
    return r;
}

int main() {
    mt19937 rng(2);
    for (int t = 0; t < 500; t++) {
        int n = 1 + rng() % 4; ll k = rng() % 15;
        Matrix<ll> m(n, 0);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) m[i][j] = rng() % 5;
        Matrix<ll> a = m ^ k, b = naive_pow(m, k);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) assert(a[i][j] == b[i][j]);
    }
    // Fibonacci sanity
    Matrix<ll> F(2, 0); F[0][0]=1; F[0][1]=1; F[1][0]=1; F[1][1]=0;
    Matrix<ll> R = F ^ 10;
    assert(R[0][0] == 89 && R[0][1] == 55 && R[1][1] == 34);
    puts("matrix: M^k vs mult ingenua (500) + fibonacci");
    return 0;
}
