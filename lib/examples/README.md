# Exemplos de Nodes e Tags para Programação Competitiva

Esta pasta contém **coleções prontas** de Nodes e Tags para usar com Segment Trees, Sparse Tables e outras estruturas de dados.

## 📁 Arquivos

- **[nodes.hpp](nodes.hpp)** - Nodes para Segment Tree / Sparse Table
- **[tags.hpp](tags.hpp)** - Tags para Lazy Propagation

## 🚀 Como Usar

### Método 1: Copiar e Colar (Recomendado para Contests)

1. Abra o arquivo correspondente (`nodes.hpp` ou `tags.hpp`)
2. Encontre o Node/Tag que você precisa
3. Copie apenas aquele struct para o seu código
4. Ajuste se necessário (raro)

**Exemplo:**
```cpp
#include <bits/stdc++.h>
using namespace std;

// Copiado de examples/nodes.hpp
struct SumNode {
    ll val = 0;
    SumNode(ll v = 0) : val(v) {}
    static inline SumNode merge(const SumNode& l, const SumNode& r) {
        return SumNode(l.val + r.val);
    }
};

// Copiado de examples/tags.hpp
struct AffineTag {
    ll mul = 1, add = 0;
    void compose(const AffineTag& t) {
        add = (add * t.mul + t.add) % MOD;
        mul = (mul * t.mul) % MOD;
    }
};

// Sua estrutura de dados
LazySegmentTree<SumNode, AffineTag> st(n);
```

### Método 2: Include (Para treino/desenvolvimento)

```cpp
#include "lib/examples/nodes.hpp"
#include "lib/examples/tags.hpp"
```

## 📚 Nodes Disponíveis

### Básicos (Idempotentes)
- `SumNode` - Soma de range
- `MinNode` / `MaxNode` - Mínimo/Máximo com índice
- `GCDNode` - GCD de range
- `XORNode` / `ANDNode` / `ORNode` - Operações bitwise

### Avançados
- `Matrix2x2Node` - Para Fibonacci, recorrências lineares
- `CountNode` - Range sum com contador
- `MinMaxNode` - Min e Max simultâneos
- `LinearFunctionNode` - **Composição de funções f(x) = ax + b**
- `AffineFunctionNode` - Para HLD não-comutativo

## 🏷️ Tags Disponíveis

### Básicos
- `AddTag` - Range add
- `SetTag` - Range assignment
- `MultiplyTag` - Range multiplication

### Compostos
- `AffineTag` - **Transformação afim ax + b** (muito comum!)
- `SetAddTag` - Set seguido de Add
- `FlipTag` - Toggle de bits

### Avançados
- `LinearFunctionTag` - **Composição de funções lineares** (muito importante!)
- `Matrix2x2Tag` - Transformações matriciais
- `ModularAffineTag` - Affine com inverso modular

## 🎯 Casos de Uso Importantes

### 1. Composição de Funções (LinearFunctionTag)

**Problema típico:** Você tem uma sequência de funções f₁, f₂, ..., fₙ onde cada fᵢ(x) = aᵢx + bᵢ. Você precisa:
- Aplicar todas as funções em sequência: (f₁ ∘ f₂ ∘ ... ∘ fₙ)(x)
- Atualizar funções em um range
- Fazer queries de composição em ranges

**Solução:**
```cpp
LazySegmentTree<LinearFunctionNode, LinearFunctionTag> st(n);

// Update: trocar função na posição i
st.update(i, i, LinearFunctionTag(2, 3)); // f(x) = 2x + 3

// Query: obter composição f_l ∘ f_{l+1} ∘ ... ∘ f_r
auto composed = st.query(l, r);
ll result = composed.eval(x); // aplica em x
```

### 2. HLD não-comutativo com funções

**Problema:** Atualizar e fazer queries de composição de funções em caminhos de uma árvore.

```cpp
HLD<LinearFunctionNode, LinearFunctionTag> hld(adj, initial_vals);
hld.update_path(u, v, LinearFunctionTag(2, 1));
auto path_fn = hld.query_path(u, v);
ll result = path_fn.eval(x);
```

### 3. Range Add e Range Assign (AffineTag)

**Problema:** Suportar dois tipos de updates:
- `a[i] = x` para todo i em [l, r]
- `a[i] += y` para todo i em [l, r]

**Solução:**
```cpp
LazySegmentTree<SumNode, AffineTag> st(n);

// Range add: a[i] += 5
st.update(l, r, AffineTag(1, 5)); // mul=1, add=5

// Range set: a[i] = 10
// Simula com: a[i] = 0*a[i] + 10, mas precisa ajustar o Node
```

### 4. Fibonacci com Matrix2x2Node

**Problema:** Calcular Fibonacci de ranges, ou aplicar recorrência linear.

```cpp
SegTree<Matrix2x2Node> st(n);
Matrix2x2Node fib(1, 1, 1, 0); // matriz de Fibonacci
st.update(i, fib);

// fib(n) = st.query(0, n-1).a[0][1]
```

## ⚡ Dicas para Contests

1. **Tenha os exemplos abertos** durante o contest
2. **Copie apenas o que precisa** - não inclua tudo
3. **Teste com casos pequenos** antes de submeter
4. **Lembre-se das propriedades:**
   - Sparse Table precisa de operação **idempotente** (min, max, gcd, and, or)
   - Lazy propagation precisa de **compose correto**
   - Composição de funções: ordem importa! (f ∘ g) ≠ (g ∘ f)

## 🔍 Referências

- **Composição de funções:** Ordem é da direita para esquerda: (f ∘ g)(x) = f(g(x))
- **Affine transformation:** f(x) = ax + b, composição: (f ∘ g)(x) = a(cx+d) + b = (ac)x + (ad+b)
- **Matrix multiplication:** Composição de transformações lineares

## 📝 Contribuindo

Se você desenvolver um Node/Tag útil durante um contest ou treino, adicione aqui para referência futura!
