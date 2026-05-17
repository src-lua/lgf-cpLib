#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Crivo de Eratóstenes
 * Complexidade: O(N log log N)
 *
 * sieve(n) → vetor com todos os primos até n (inclusive).
 */

vector<int> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= n; p++) {
        if (is_prime[p]) {
            primes.push_back(p);
            if ((long long)p * p <= n)
                for (int i = p * p; i <= n; i += p)
                    is_prime[i] = false;
        }
    }
    return primes;
}
