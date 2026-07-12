#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Matrix — Matriz quadrada com multiplicação e exponenciação rápida
 * Complexidade: O(n³ log k) para M^k
 *
 * Use com mint/mll para operações modulares automáticas.
 *
 * Matrix<T> M(n)   → identidade n×n
 * Matrix<T> M(n,0) → matriz n×n zerada
 * M[i][j]          → acesso direto
 * A * B            → multiplicação O(n³)
 * M ^ k            → M^k por exponenciação rápida
 */

template<typename T>
struct Matrix {
    int n;
    vector<vector<T>> mat;

    Matrix(int n, int identity = 1) : n(n), mat(n, vector<T>(n, T(0))) {
        if (identity) for (int i = 0; i < n; i++) mat[i][i] = T(1);
    }

    vector<T>& operator[](int i) { return mat[i]; }
    const vector<T>& operator[](int i) const { return mat[i]; }

    Matrix operator*(const Matrix& rhs) const {
        Matrix res(n, 0);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) if (mat[i][k] != T(0))
                for (int j = 0; j < n; j++)
                    res[i][j] = res[i][j] + mat[i][k] * rhs.mat[k][j];
        return res;
    }

    Matrix operator^(long long b) const {
        Matrix res(n), a = *this;
        for (; b > 0; b >>= 1, a = a * a)
            if (b & 1) res = res * a;
        return res;
    }
};
