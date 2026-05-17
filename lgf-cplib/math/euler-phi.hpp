#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Crivo Linear — O(N)
 *
 * linear_sieve(n) → {primes, phi}
 *   primes : todos os primos até n (inclusive)
 *   phi    : phi[i] = φ(i) para i em [0, n]
 */

pair<vector<int>, vector<int>> linear_sieve(int n) {
    vector<int> phi(n + 1, 0), primes;
    vector<bool> composite(n + 1, false);
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!composite[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            if ((long long)i * p > n) break;
            composite[i * p] = true;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
    return {primes, phi};
}
