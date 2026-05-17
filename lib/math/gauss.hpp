#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Eliminação Gaussiana (RREF) — O(N^2 * M)
 * Funciona com double ou Mint<T, mod>.
 *
 * gauss(A, b) → resolve Ax = b.
 *   Retorna {x, true} se única, {x, false} se inconsistente/sub-determinado.
 */

template<typename T>
pair<vector<T>, bool> gauss(vector<vector<T>> A, vector<T> b) {
    int n = A.size();
    for (int i = 0; i < n; i++) A[i].push_back(b[i]);
    int m = n + 1, rank = 0;
    for (int col = 0; col < n && rank < n; col++) {
        int sel = rank;
        for (int i = rank + 1; i < n; i++)
            if (abs(A[i][col]) > abs(A[sel][col])) sel = i;
        if (!(bool)A[sel][col]) continue;
        swap(A[sel], A[rank]);
        T iv = T(1) / A[rank][col];
        for (int j = col; j < m; j++) A[rank][j] = A[rank][j] * iv;
        for (int i = 0; i < n; i++) {
            if (i == rank || !(bool)A[i][col]) continue;
            T f = A[i][col];
            for (int j = col; j < m; j++) A[i][j] = A[i][j] - f * A[rank][j];
        }
        rank++;
    }
    if (rank < n) return {{}, false};
    vector<T> x(n);
    for (int i = 0; i < n; i++) x[i] = A[i].back();
    return {x, true};
}
