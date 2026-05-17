#pragma once
#include <bits/stdc++.h>
using namespace std;

/* Manacher's Algorithm (Palindrome Detection)
 * Encontra todos os palíndromos em uma string em tempo linear.
 * Complexidade: O(N) onde N é o tamanho da string.
 * Memória: O(N)
 * Funções:
 * - manacher(s): arr[i] = tamanho do maior palíndromo centrado em i.
 * - palindrome: Struct para verificar se s[i..j] é palíndromo em O(1).
 * - pal_begin(s): arr[i] = tamanho do maior palíndromo começando em i.
 * - pal_end(s):   arr[i] = tamanho do maior palíndromo terminando em i.
 */

template<typename T>
vector<int> manacher(const T& s) {
    int l = 0, r = -1, n = s.size();
    vector<int> d1(n), d2(n);
    for (int i = 0; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i);
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        k++;
        while (i + k <= n && i - k >= 0 && s[i + k - 1] == s[i - k])
            k++;
        d2[i] = --k;
        if (i + k - 1 > r) l = i - k, r = i + k - 1;
    }
    vector<int> ret(2 * n - 1);
    for (int i = 0; i < n; i++) ret[2 * i] = 2 * d1[i] - 1;
    for (int i = 0; i < n - 1; i++) ret[2 * i + 1] = 2 * d2[i + 1];
    return ret;
}

template<typename T>
struct palindrome {
    vector<int> man;

    palindrome(const T& s) : man(manacher(s)) {}

    bool query(int i, int j) {
        return man[i + j] >= j - i + 1;
    }
};

template<typename T>
vector<int> pal_begin(const T& s) {
    int n = s.size() - 1;
    vector<int> ret(s.size());
    palindrome<T> p(s);
    ret[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        ret[i] = min(ret[i + 1] + 2, n - i + 1);
        while (!p.query(i, i + ret[i] - 1)) ret[i]--;
    }
    return ret;
}

template<typename T>
vector<int> pal_end(const T& s) {
    vector<int> ret(s.size());
    palindrome<T> p(s);
    ret[0] = 1;
    for (int i = 1; i < s.size(); i++) {
        ret[i] = min(ret[i - 1] + 2, i + 1);
        while (!p.query(i - ret[i] + 1, i)) ret[i]--;
    }
    return ret;
}