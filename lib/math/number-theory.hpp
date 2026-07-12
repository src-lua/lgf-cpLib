#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* GCD / LCM — O(log min(a, b)) */
ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}
ll lcm(ll a, ll b) {
  return a / gcd(a, b) * b;
}

/* Divisores de n — O(sqrt(N))
 * Retorna lista de divisores em ordem crescente.
 */
vector<ll> divisors(ll n) {
  vector<ll> lo, hi;
  for (ll i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      lo.push_back(i);
      if (i != n / i) hi.push_back(n / i);
    }
  }
  reverse(hi.begin(), hi.end());
  lo.insert(lo.end(), hi.begin(), hi.end());
  return lo;
}

/* Fatoração em primos — O(sqrt(N))
 * Retorna lista de {primo, expoente} em ordem crescente.
 */
vector<pair<ll, int>> factorize(ll n) {
  vector<pair<ll, int>> factors;
  for (ll p = 2; p * p <= n; p++) {
    if (n % p == 0) {
      int exp = 0;
      while (n % p == 0) {
        n /= p;
        exp++;
      }
      factors.push_back({p, exp});
    }
  }
  if (n > 1) factors.push_back({n, 1});
  return factors;
}

/* CRT — Teorema Chinês dos Restos — O(log min(m1, m2))
 * Retorna {x, lcm} com x ≡ a1 (mod m1), x ≡ a2 (mod m2).
 * Retorna {0, 0} se o sistema for incompatível.
 */
pair<ll, ll> crt(ll a1, ll m1, ll a2, ll m2) {
  ll g = gcd(m1, m2);
  if ((a2 - a1) % g != 0) return {0, 0};
  ll mod = m1 / g * m2;
  ll a = m1 / g, b = m2 / g, x = 1, y = 0;
  for (ll ta = a, tb = b; tb;) {
    ll q = ta / tb;
    ta -= q * tb;
    swap(ta, tb);
    x -= q * y;
    swap(x, y);
  }
  x = (x % (m2 / g) + m2 / g) % (m2 / g);
  ll step = (a2 - a1) / g % (m2 / g) * x % (m2 / g);
  ll result = (a1 + m1 * step) % mod;
  return {(result + mod) % mod, mod};
}

/* Fatoração com primos pré-computados — O(π(sqrt(N)))
 * Útil após sieve(sqrt(n)) para fatorar vários números.
 * primes deve conter todos os primos até sqrt(n).
 */
vector<pair<ll, int>> factorize(ll n, const vector<int> &pr) {
  vector<pair<ll, int>> factors;
  for (int p : pr) {
    if ((ll)p * p > n) break;
    if (n % p == 0) {
      int exp = 0;
      while (n % p == 0) {
        n /= p;
        exp++;
      }
      factors.push_back({p, exp});
    }
  }
  if (n > 1) factors.push_back({n, 1});
  return factors;
}
