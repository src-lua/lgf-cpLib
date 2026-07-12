#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* Linear Basis (Base Linear XOR)
 * Complexidade: O(B) por operação, onde B = número de bits (63 para ll)
 * Memória: O(B)
 *
 * Métodos:
 *   insert(x)    → insere x; retorna true se x é linearmente independente
 *   contains(x)  → true se x é XOR de algum subconjunto da base
 *   max_xor(x=0) → maior XOR de x com qualquer subconjunto da base
 *   min_xor()    → menor XOR não-nulo possível (0 se base incompleta)
 *   size()       → número de elementos linearmente independentes
 *   merge(other) → une duas bases (insere todos os elementos de other)
 *
 * Observações:
 *   - Base em forma reduzida (cada bit pivot aparece em apenas uma linha).
 *   - Para k-ésimo XOR crescente, use reduce() e trate como número binário.
 */

template<typename T = ll, int B = 63>
struct LinearBasis {
    array<T, B + 1> basis{};
    int sz = 0;

    bool insert(T x) {
        for (int i = B; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;
            if (!basis[i]) {
                basis[i] = x;
                sz++;
                return true;
            }
            x ^= basis[i];
        }
        return false;
    }

    bool contains(T x) const {
        for (int i = B; i >= 0; i--) {
            if (!((x >> i) & 1)) continue;
            if (!basis[i]) return false;
            x ^= basis[i];
        }
        return true;
    }

    T max_xor(T x = 0) const {
        for (int i = B; i >= 0; i--)
            x = max(x, x ^ basis[i]);
        return x;
    }

    T min_xor() const {
        for (int i = 0; i <= B; i++)
            if (basis[i]) return basis[i];
        return 0;
    }

    int size() const { return sz; }

    void merge(const LinearBasis& other) {
        for (int i = B; i >= 0; i--)
            if (other.basis[i]) insert(other.basis[i]);
    }

    /* Reduz a base para forma escalonada reduzida (cada pivot tem 1 bit).
     * Necessário para consultas de k-ésimo XOR.
     * Após reduce(), qualquer subconjunto gera um XOR distinto:
     * é possível enumerar todos os 2^sz XORs possíveis.
     */
    void reduce() {
        for (int i = B; i >= 0; i--) {
            if (!basis[i]) continue;
            for (int j = i + 1; j <= B; j++)
                if ((basis[j] >> i) & 1) basis[j] ^= basis[i];
        }
    }

    /* k-ésimo menor XOR (0-indexado) entre todos os 2^sz subconjuntos.
     * Requer reduce() antes. Se sz < B+1, XOR=0 = subconjunto vazio.
     * k=0 → 0; k=1 → menor XOR não-nulo, etc.
     */
    T kth(ll k) const {
        vector<T> elems;
        for (int i = 0; i <= B; i++)
            if (basis[i]) elems.push_back(basis[i]);
        // elems está em ordem crescente de bit mais significativo
        if (k >= (1LL << (int)elems.size())) return -1; // k fora do range
        T res = 0;
        for (int i = 0; i < (int)elems.size(); i++)
            if ((k >> i) & 1) res ^= elems[i];
        return res;
    }
};
