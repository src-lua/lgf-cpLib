#pragma once
#include "fft.hpp"

/* FFT Mod — Convolução modular com mod arbitrário
 * Complexidade: O(N log N) (~2x mais lento que FFT ou NTT)
 *
 * convMod<mod>(a, b) → c[k] = (Σ a[i]*b[k-i]) % mod
 *
 * Entradas devem estar em [0, mod).
 * Seguro se N·log₂N·mod < 8.6·10¹⁴.
 *
 * Alta precisão sem mod: troque cut = 1<<15 e remova os % mod.
 */

template<int mod>
vector<long long> convMod(
    const vector<long long>& a, const vector<long long>& b) {
    if (a.empty() || b.empty()) return {};
    vector<long long> res(a.size() + b.size() - 1);
    int B = 32 - __builtin_clz(res.size()), n = 1 << B;
    int cut = (int)sqrt(mod); // alta precisão: use 1<<15 e tire os % mod abaixo
    vector<CD> L(n), R(n), outs(n), outl(n);
    for (int i = 0; i < (int)a.size(); i++)
        L[i] = CD((int)a[i] / cut, (int)a[i] % cut);
    for (int i = 0; i < (int)b.size(); i++)
        R[i] = CD((int)b[i] / cut, (int)b[i] % cut);
    fft(L); fft(R);
    for (int i = 0; i < n; i++) {
        int j = -i & (n-1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / CD(0, 1);
    }
    fft(outl); fft(outs);
    for (int i = 0; i < (int)res.size(); i++) {
        // alta precisão: tire os % mod nas linhas abaixo
        long long av = (long long)(real(outl[i]) + .5) % mod;
        long long bv = (long long)(imag(outl[i]) + .5)
                     + (long long)(real(outs[i]) + .5);
        long long cv = (long long)(imag(outs[i]) + .5);
        res[i] = ((av * cut + bv) % mod * cut + cv) % mod;
    }
    return res;
}
