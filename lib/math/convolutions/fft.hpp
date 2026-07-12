#pragma once
#include <bits/stdc++.h>
using namespace std;
using ld = double; // troque por long double para mais precisão
using CD = complex<ld>;

/* FFT — Fast Fourier Transform
 * Complexidade: O(N log N)
 *
 * fft(a)       → transforma a no lugar; |a| é potência de 2
 * conv(a, b)   → convolução: c[k] = Σ a[i]*b[k-i]
 *
 * Precisão: seguro se (Σa²+Σb²)*log₂N < 9·10¹⁴.
 * Para coeficientes grandes ou módulo, use fft-mod ou NTT.
 */

void fft(vector<CD> &a) {
  int n = a.size(), log_n = 31 - __builtin_clz(n);

  static vector<complex<long double>> R(2, 1);
  static vector<CD> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    auto x = polar(1.0L, acos(-1.0L) / k);
    R.resize(n);
    rt.resize(n);
    for (int i = k; i < 2 * k; i++)
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }

  vector<int> rev(n);
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i / 2] | (i & 1) << log_n) / 2;
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);

  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        auto x = (ld *)&rt[j + k], y = (ld *)&a[i + j + k];
        CD z(x[0] * y[0] - x[1] * y[1],
             x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}

vector<ld> conv(const vector<ld> &a, const vector<ld> &b) {
  if (a.empty() || b.empty()) return {};
  vector<ld> res(a.size() + b.size() - 1);
  int n = 1 << (32 - __builtin_clz(res.size()));
  vector<CD> in(n), out(n);
  copy(begin(a), end(a), begin(in));
  for (int i = 0; i < (int)b.size(); i++) in[i].imag(b[i]);
  fft(in);
  for (auto &x : in) x *= x;
  for (int i = 0; i < n; i++)
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  for (int i = 0; i < (int)res.size(); i++)
    res[i] = imag(out[i]) / (4 * n);
  return res;
}
