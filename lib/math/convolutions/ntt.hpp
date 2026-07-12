#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* NTT — Number Theoretic Transform
 * Complexidade: O(N log N)
 *
 * NTT<mod, g>::conv(a, b) → c[k] = (Σ a[i]*b[k-i]) % mod
 *
 * Entradas devem estar em [0, mod).
 * mod é primo 2^a·b+1; g é sua raiz primitiva.
 *
 * Opções de {mod, g}:
 * {998244353, 3} → 119·2²³+1, mais comum, N ≤ 2²³
 * {469762049, 3} → 7·2²⁶+1, N ≤ 2²⁶
 * {167772161, 3} → 5·2²⁵+1, N ≤ 2²⁵
 * {2013265921, 31} → 15·2²⁷+1, N ≤ 2²⁷ (mod > 10⁹)
 * {2281701377, 3} → 17·2²⁷+1, N ≤ 2²⁷ (mod > 10⁹)
 * {7340033, 5} → 7·2²⁰+1, N ≤ 2²⁰ (menor mod)
 * {9223372036737335297LL,3} → 549755813881·2²⁴+1, N≤2²⁴
 *   (mod~2⁶³, ll)
 */

template <ll mod, ll g>
struct NTT {
  static ll fexp(ll a, ll b) {
    ll res = 1;
    a %= mod;
    for (; b > 0; b >>= 1, a = a * a % mod)
      if (b & 1) res = res * a % mod;
    return res;
  }

  static void ntt(vector<ll> &a) {
    int n = a.size(), log_n = 31 - __builtin_clz(n);
    static vector<ll> rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
      rt.resize(n);
      ll z[] = {1, fexp(g, mod >> s)};
      for (int i = k; i < 2 * k; i++)
        rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    vector<int> rev(n);
    for (int i = 0; i < n; i++)
      rev[i] = (rev[i / 2] | (i & 1) << log_n) / 2;
    for (int i = 0; i < n; i++)
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
      for (int i = 0; i < n; i += 2 * k)
        for (int j = 0; j < k; j++) {
          ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
          a[i + j + k] = ai - z + (z > ai ? mod : 0);
          ai += z - (ai + z >= mod ? mod : 0);
        }
  }

  static vector<ll> conv(vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};
    int s = a.size() + b.size() - 1;
    int n = 1 << (32 - __builtin_clz(s));
    a.resize(n), b.resize(n); ntt(a), ntt(b);
    ll inv = fexp(n, mod - 2);
    vector<ll> out(n);
    for (int i = 0; i < n; i++)
      out[-i & (n - 1)] = a[i] * b[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
  }
};
