#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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
      if ((ll)p * p <= n)
        for (int i = p * p; i <= n; i += p) is_prime[i] = false;
    }
  }
  return primes;
}

/* Crivo de menor fator primo (SPF) — O(N log log N) build
 * spf[i] = menor primo de i; spf[i] == i indica primo.
 * Permite fatorar qualquer x <= n em O(log x).
 *
 * auto spf = spf_sieve(n);
 * factor(x, spf) → pares {primo, expoente} ordenados.
 */

vector<int> spf_sieve(int n) {
  vector<int> spf(n + 1);
  iota(spf.begin(), spf.end(), 0);
  for (int i = 2; (ll)i * i <= n; i++)
    if (spf[i] == i)
      for (int j = i * i; j <= n; j += i)
        if (spf[j] == j) spf[j] = i;
  return spf;
}

vector<pair<int, int>> factor(int x, const vector<int> &spf) {
  vector<pair<int, int>> f;
  while (x > 1) {
    int p = spf[x], e = 0;
    while (x % p == 0) {
      x /= p;
      e++;
    }
    f.push_back({p, e});
  }
  return f;
}

/* Divisores de x fora de ordem — O(d(x)).
 * Requer x dentro do crivo usado para gerar spf.
 * Aplique sort() ao retorno quando precisar de ordem.
 */

vector<int> divisors(int x, const vector<int> &spf) {
  vector<int> divs = {1};
  for (auto [p, e] : factor(x, spf)) {
    int sz = divs.size(), pk = 1;
    for (int k = 0; k < e; k++) {
      pk *= p;
      for (int i = 0; i < sz; i++) divs.push_back(divs[i] * pk);
    }
  }
  return divs;
}
