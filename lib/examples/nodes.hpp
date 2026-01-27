#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

/* Coleção de Nodes para Segment Tree / Sparse Table
 * Copie o Node que você precisa para o seu código.
 * Requisitos: Cada Node deve ter static merge() e construtor identidade.
 * Para Lazy: Node deve ter apply(TAG, l, r).
 */

// ============================================================================
// NODES BÁSICOS (Idempotentes - para Sparse Table também)
// ============================================================================

// --- Sum Node (Soma) ---
struct SumNode {
    ll val = 0;
    SumNode(ll v = 0) : val(v) {}

    static inline SumNode merge(const SumNode& l, const SumNode& r) {
        return SumNode(l.val + r.val);
    }

    // Para Lazy com AddTag
    void apply(ll add, int len) {
        val += add * len;
    }
};

// --- Min Node com Índice ---
struct MinNode {
    ll val = LLONG_MAX;
    int pos = -1;
    MinNode(ll v = LLONG_MAX, int p = -1) : val(v), pos(p) {}

    static inline MinNode merge(const MinNode& l, const MinNode& r) {
        return l.val <= r.val ? l : r;
    }
};

// --- Max Node com Índice ---
struct MaxNode {
    ll val = LLONG_MIN;
    int pos = -1;
    MaxNode(ll v = LLONG_MIN, int p = -1) : val(v), pos(p) {}

    static inline MaxNode merge(const MaxNode& l, const MaxNode& r) {
        return l.val >= r.val ? l : r;
    }
};

// --- GCD Node ---
struct GCDNode {
    ll val = 0;
    GCDNode(ll v = 0) : val(v) {}

    static inline GCDNode merge(const GCDNode& l, const GCDNode& r) {
        return GCDNode(__gcd(l.val, r.val));
    }
};

// --- XOR Node ---
struct XORNode {
    ll val = 0;
    XORNode(ll v = 0) : val(v) {}

    static inline XORNode merge(const XORNode& l, const XORNode& r) {
        return XORNode(l.val ^ r.val);
    }
};

// --- AND Node ---
struct ANDNode {
    ll val = -1LL; // todos os bits setados
    ANDNode(ll v = -1LL) : val(v) {}

    static inline ANDNode merge(const ANDNode& l, const ANDNode& r) {
        return ANDNode(l.val & r.val);
    }
};

// --- OR Node ---
struct ORNode {
    ll val = 0;
    ORNode(ll v = 0) : val(v) {}

    static inline ORNode merge(const ORNode& l, const ORNode& r) {
        return ORNode(l.val | r.val);
    }
};

// ============================================================================
// NODES AVANÇADOS
// ============================================================================

// --- Matrix 2x2 Node (para Fibonacci, recorrências lineares) ---
// Exemplo: fib(n) = [[1,1],[1,0]]^n * [[1],[0]]
const ll MOD = 1e9 + 7;

struct Matrix2x2Node {
    ll a[2][2];

    Matrix2x2Node() {
        memset(a, 0, sizeof a);
        a[0][0] = a[1][1] = 1; // identidade
    }

    Matrix2x2Node(ll a00, ll a01, ll a10, ll a11) {
        a[0][0] = a00; a[0][1] = a01;
        a[1][0] = a10; a[1][1] = a11;
    }

    static inline Matrix2x2Node merge(const Matrix2x2Node& l,
                                       const Matrix2x2Node& r) {
        Matrix2x2Node res;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++) {
                res.a[i][j] = 0;
                for(int k = 0; k < 2; k++)
                    res.a[i][j] = (res.a[i][j] + l.a[i][k] * r.a[k][j]) % MOD;
            }
        return res;
    }
};

// --- Range Sum com contador ---
// Útil para queries tipo: "quantos elementos < x no range [l,r]"
struct CountNode {
    ll sum = 0;
    int cnt = 0;
    CountNode(ll s = 0, int c = 0) : sum(s), cnt(c) {}

    static inline CountNode merge(const CountNode& l, const CountNode& r) {
        return CountNode(l.sum + r.sum, l.cnt + r.cnt);
    }
};

// --- Min e Max simultâneos ---
struct MinMaxNode {
    ll minVal = LLONG_MAX;
    ll maxVal = LLONG_MIN;
    MinMaxNode(ll v = 0) : minVal(v), maxVal(v) {}
    MinMaxNode(ll mn, ll mx) : minVal(mn), maxVal(mx) {}

    static inline MinMaxNode merge(const MinMaxNode& l, const MinMaxNode& r) {
        return MinMaxNode(min(l.minVal, r.minVal), max(l.maxVal, r.maxVal));
    }
};

// ============================================================================
// NODES PARA LAZY PROPAGATION
// ============================================================================

// --- Sum Node com Lazy Add/Set ---
struct SumNodeLazy {
    ll val = 0;
    SumNodeLazy(ll v = 0) : val(v) {}

    static inline SumNodeLazy merge(const SumNodeLazy& l,
                                     const SumNodeLazy& r) {
        return SumNodeLazy(l.val + r.val);
    }

    // Apply AddTag
    template<typename AddTag>
    void applyAdd(const AddTag& t, int l, int r) {
        val += t.add * (r - l + 1);
    }

    // Apply SetTag
    template<typename SetTag>
    void applySet(const SetTag& t, int l, int r) {
        if(t.has) val = t.val * (r - l + 1);
    }

    // Apply AffineTag (ax + b)
    template<typename AffineTag>
    void applyAffine(const AffineTag& t, int l, int r) {
        val = (val * t.mul + t.add * (r - l + 1)) % MOD;
    }
};

// --- Função Linear Node (composição de funções: f(x) = ax + b) ---
// Muito útil para composição de funções em árvores
struct LinearFunctionNode {
    ll a = 1, b = 0; // f(x) = ax + b

    LinearFunctionNode(ll _a = 1, ll _b = 0) : a(_a % MOD), b(_b % MOD) {}

    // Composição: (f ∘ g)(x) = f(g(x)) = f(gx + h) = a(gx + h) + b
    // = (ag)x + (ah + b)
    static inline LinearFunctionNode merge(const LinearFunctionNode& f,
                                            const LinearFunctionNode& g) {
        return LinearFunctionNode(
            (f.a * g.a) % MOD,
            (f.a * g.b + f.b) % MOD
        );
    }

    // Aplica a função: f(x) = ax + b
    ll eval(ll x) const {
        return (a * x + b) % MOD;
    }
};

// --- Affine Function Node (para HLD não-comutativo com funções afins) ---
// Similar ao LinearFunctionNode mas com semântica específica para HLD
struct AffineFunctionNode {
    ll mul = 1, add = 0;

    AffineFunctionNode(ll m = 1, ll a = 0) : mul(m % MOD), add(a % MOD) {}

    static inline AffineFunctionNode merge(const AffineFunctionNode& l,
                                            const AffineFunctionNode& r) {
        return AffineFunctionNode(
            (l.mul * r.mul) % MOD,
            (l.mul * r.add + l.add) % MOD
        );
    }
};

// ============================================================================
// EXEMPLOS DE USO
// ============================================================================

/*
// --- Segment Tree com SumNode ---
SegTree<SumNode> st(n);
st.update(i, SumNode(val));
SumNode result = st.query(l, r);
cout << result.val << '\n';

// --- Sparse Table com MinNode (RMQ) ---
SparseTable<MinNode> sp(v);
MinNode minimo = sp.query(l, r);
cout << "Min: " << minimo.val << " at position " << minimo.pos << '\n';

// --- Matrix para Fibonacci ---
SegTree<Matrix2x2Node> st(n);
Matrix2x2Node fib(1, 1, 1, 0);
st.update(i, fib);

// --- Composição de Funções Lineares ---
SegTree<LinearFunctionNode> st(n);
st.update(i, LinearFunctionNode(2, 3)); // f(x) = 2x + 3
st.update(j, LinearFunctionNode(4, 1)); // g(x) = 4x + 1
// merge(f, g) = f(g(x)) = 2(4x + 1) + 3 = 8x + 5
LinearFunctionNode composed = st.query(l, r);
ll result = composed.eval(x);
*/
