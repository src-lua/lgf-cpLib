#pragma once
#include "fft.hpp"
using ll = long long;

/* FFT Mod — Convolução modular com mod arbitrário
 * Complexidade: O(N log N) (~2x mais lento que FFT ou NTT)
 *
 * convMod<mod>(a, b) → c[k] = (Σ a[i]*b[k-i]) % mod
 *
 * Entradas devem estar em [0, mod).
 * Seguro se N·log₂N·mod < 8.6·10¹⁴.
 *
 * Sem mod: use cut = 1<<15 e remova os operadores % mod.
 */

template <int mod>
vector<ll> convMod(const vector<ll> &a, const vector<ll> &b) {
  if (a.empty() || b.empty()) return {};
  vector<ll> res(a.size() + b.size() - 1);
  int log_n = 32 - __builtin_clz(res.size());
  int n = 1 << log_n;
  // Para alta precisão, use 1<<15 e tire os % mod abaixo.
  int cut = (int)sqrt(mod);
  vector<CD> L(n), R(n), outs(n), outl(n);
  for (int i = 0; i < (int)a.size(); i++)
    L[i] = CD((int)a[i] / cut, (int)a[i] % cut);
  for (int i = 0; i < (int)b.size(); i++)
    R[i] = CD((int)b[i] / cut, (int)b[i] % cut);
  fft(L), fft(R);
  for (int i = 0; i < n; i++) {
    int j = -i & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / CD(0, 1);
  }
  fft(outl), fft(outs);
  for (int i = 0; i < (int)res.size(); i++) {
    // alta precisão: tire os % mod nas linhas abaixo
    ll av = (ll)(real(outl[i]) + .5) % mod;
    ll bv = (ll)(imag(outl[i]) + .5) + (ll)(real(outs[i]) + .5);
    ll cv = (ll)(imag(outs[i]) + .5);
    res[i] = ((av * cut + bv) % mod * cut + cv) % mod;
  }
  return res;
}
