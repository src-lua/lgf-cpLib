#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

/* Colecao de Tags para Lazy Propagation
 * Copie o Tag que voce precisa para o seu codigo.
 * Requisitos: Cada Tag deve ter compose() e construtor identidade.
 * Tag.compose(other): Aplica other sobre this (this = this o other).
 */

const ll MOD = 1e9 + 7;

// ============================================================================
// TAGS BASICOS
// ============================================================================

// --- Add Tag (Range Add) ---
// Operacao: a[i] += x para todo i em [l, r]
struct AddTag {
    ll add = 0;

    void compose(const AddTag& t) {
        add += t.add;
    }

    // Uso com Node:
    // void Node::apply(const AddTag& t, int l, int r) {
    //     val += t.add * (r - l + 1);
    // }
};

// --- Set Tag (Range Assignment) ---
// Operacao: a[i] = x para todo i em [l, r]
struct SetTag {
    ll val = 0;
    bool has = false;

    void compose(const SetTag& t) {
        if(t.has) {
            val = t.val;
            has = true;
        }
    }

    // Uso com Node:
    // void Node::apply(const SetTag& t, int l, int r) {
    //     if(t.has) val = t.val * (r - l + 1);
    // }
};

// --- Multiply Tag (Range Multiplication) ---
// Operacao: a[i] *= x para todo i em [l, r]
struct MultiplyTag {
    ll mul = 1;

    void compose(const MultiplyTag& t) {
        mul = (mul * t.mul) % MOD;
    }

    // Uso com Node:
    // void Node::apply(const MultiplyTag& t, int l, int r) {
    //     val = (val * t.mul) % MOD;
    // }
};

// ============================================================================
// TAGS COMPOSTOS
// ============================================================================

// --- Affine Tag (ax + b) - Transformação Afim ---
// Operacao: a[i] = a[i] * mul + add
// MUITO COMUM em problemas de lazy propagation!
struct AffineTag {
    ll mul = 1, add = 0;

    // Composicao: (f o g)(x) onde f = this, g = t
    // f(g(x)) = f(x*g.mul + g.add) = (x*g.mul + g.add)*f.mul + f.add
    //         = x*(g.mul*f.mul) + (g.add*f.mul + f.add)
    void compose(const AffineTag& t) {
        add = (add * t.mul + t.add) % MOD;
        mul = (mul * t.mul) % MOD;
    }

    // Uso com Node:
    // void Node::apply(const AffineTag& t, int l, int r) {
    //     val = (val * t.mul + t.add * (r - l + 1)) % MOD;
    // }
};

// --- Set + Add Tag (Primeiro Set, depois Add) ---
// Mais eficiente que ter tags separadas
struct SetAddTag {
    ll set_val = 0;
    ll add_val = 0;
    bool has_set = false;

    // Composicao correta:
    // Se t tem set: descarta tudo e usa set de t (depois aplica add)
    // Se t nao tem set: aplica add de t sobre o que ja existe
    void compose(const SetAddTag& t) {
        if(t.has_set) {
            set_val = t.set_val;
            add_val = t.add_val;
            has_set = true;
        } else {
            if(has_set) {
                add_val += t.add_val;
            } else {
                add_val += t.add_val;
            }
        }
    }

    // Uso com Node:
    // void Node::apply(const SetAddTag& t, int l, int r) {
    //     if(t.has_set) {
    //         val = (t.set_val + t.add_val) * (r - l + 1);
    //     } else {
    //         val += t.add_val * (r - l + 1);
    //     }
    // }
};

// --- Flip/Toggle Tag (para bits) ---
// Operacao: a[i] ^= 1 (inverte bits)
struct FlipTag {
    int flip = 0; // 0 = nao faz nada, 1 = inverte

    void compose(const FlipTag& t) {
        flip ^= t.flip;
    }

    // Uso com Node (assumindo Node guarda count de 1s):
    // void Node::apply(const FlipTag& t, int l, int r) {
    //     if(t.flip) val = (r - l + 1) - val; // inverte count
    // }
};

// ============================================================================
// TAGS AVANCADOS
// ============================================================================

// --- Linear Function Tag (Composicao de funções f(x) = ax + b) ---
// Usado em HLD nao-comutativo, DP com funções lineares, etc.
// MUITO IMPORTANTE para problemas de composição de funções!
struct LinearFunctionTag {
    ll a = 1, b = 0; // f(x) = ax + b

    LinearFunctionTag(ll _a = 1, ll _b = 0) : a(_a % MOD), b(_b % MOD) {}

    // Composicao: (f o g)(x) = f(g(x))
    // Se f = this = (a, b) e g = t = (c, d)
    // f(g(x)) = f(cx + d) = a(cx + d) + b = (ac)x + (ad + b)
    void compose(const LinearFunctionTag& t) {
        b = (a * t.b + b) % MOD;
        a = (a * t.a) % MOD;
    }

    // Aplica a função
    ll eval(ll x) const {
        return (a * x + b) % MOD;
    }
};

// --- Matrix 2x2 Tag (para transformações matriciais) ---
// Util para problemas de Fibonacci, recorrências lineares
struct Matrix2x2Tag {
    ll m[2][2];

    Matrix2x2Tag() {
        memset(m, 0, sizeof m);
        m[0][0] = m[1][1] = 1; // identidade
    }

    Matrix2x2Tag(ll a, ll b, ll c, ll d) {
        m[0][0] = a; m[0][1] = b;
        m[1][0] = c; m[1][1] = d;
    }

    void compose(const Matrix2x2Tag& t) {
        ll res[2][2];
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++) {
                res[i][j] = 0;
                for(int k = 0; k < 2; k++)
                    res[i][j] = (res[i][j] + m[i][k] * t.m[k][j]) % MOD;
            }
        memcpy(m, res, sizeof m);
    }
};

// --- Modular Affine Tag (com inverso modular) ---
// Similar ao AffineTag mas garante que mul tem inverso modular
struct ModularAffineTag {
    ll mul = 1, add = 0;

    ModularAffineTag(ll m = 1, ll a = 0) : mul(m), add(a) {}

    // Inverso modular via Fermat (requer MOD primo)
    ll inv(ll x) const {
        ll res = 1, p = x, exp = MOD - 2;
        while(exp) {
            if(exp & 1) res = (res * p) % MOD;
            p = (p * p) % MOD;
            exp >>= 1;
        }
        return res;
    }

    void compose(const ModularAffineTag& t) {
        add = (add * t.mul + t.add) % MOD;
        mul = (mul * t.mul) % MOD;
    }
};

// ============================================================================
// EXEMPLOS DE USO
// ============================================================================

/*
// --- LazySegTree com AffineTag ---
LazySegmentTree<SumNodeLazy, AffineTag> st(n);
st.update(l, r, AffineTag(2, 3)); // a[i] = 2*a[i] + 3
auto result = st.query(l, r);

// --- Composicao de Funções Lineares ---
// Problema: Aplicar sequência de funções f1, f2, ..., fk em um ponto x
LazySegmentTree<LinearFunctionNode, LinearFunctionTag> st(n);
st.update(i, i, LinearFunctionTag(2, 3)); // f(x) = 2x + 3
st.update(j, j, LinearFunctionTag(4, 1)); // g(x) = 4x + 1
// Query [i, j] retorna a composição f_i o f_{i+1} o ... o f_j
auto composed = st.query(l, r);
ll result = composed.eval(x);

// --- Set + Add ---
LazySegmentTree<SumNode, SetAddTag> st(n);
SetAddTag t1; t1.has_set = true; t1.set_val = 5; // a[i] = 5
st.update(l, r, t1);
st.update(l, r, AddTag{3}); // a[i] += 3 (agora a[i] = 8)

// --- HLD nao-comutativo com funções ---
// lib/graphs/hld/hld-non-commutative-lazy.hpp
HLD<LinearFunctionNode, LinearFunctionTag> hld(adj, initial_vals);
hld.update_path(u, v, LinearFunctionTag(2, 1)); // aplica f(x)=2x+1 no caminho
auto path_function = hld.query_path(u, v);
ll result = path_function.eval(x);
*/
