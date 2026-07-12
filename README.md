# lgf-cplib

Caderno de biblioteca para programação competitiva (ICPC /
Maratona) da **Lua Guimarães Fernandes** — CIn-UFPE.

Os algoritmos ficam em `lib/`, limitados a **65 colunas** para
caber na fonte do caderno impresso (3 colunas, paisagem). Um
gerador em Rust + Typst produz o PDF final em `print/`.

## Estrutura

```text
lib/                algoritmos (.hpp), organizados por tópico
  data-structures/  graphs/  math/  string/  geometry/
  others/           theory/  (páginas teóricas em .typ)
generator/          gerador do PDF (Rust + Typst)
  src/              binário notebook-gen (Rust)
  notebook.typ      template colorido
  notebook-bw.typ   template preto e branco
  contents.txt      o que entra no caderno e em que ordem
  generate_pdf.sh   build local (precisa de `cargo` + `typst`)
  portable/         build com binários embutidos (sem toolchain)
tests/              suíte de testes (format + compile + stress)
scripts/            common.sh — cores/spinner compartilhados
print/              saída: notebook.pdf / notebook-bw.pdf
snippets/           snippets.json / snippets.md (VS Code)
```

## Gerar o PDF

### Local (precisa de `cargo` e `typst`)

```sh
bash generator/generate_pdf.sh          # colorido -> print/notebook.pdf
bash generator/generate_pdf.sh --bw     # p&b      -> print/notebook-bw.pdf
```

### Portable (sem instalar nada)

Usa binários (`notebook-gen` + `typst`) já embutidos em
`generator/portable/<os>/bin/`, então não precisa de Rust nem
Typst instalados — só do repositório em mãos.

```sh
bash generator/portable/macos/run.sh          # macOS
bash generator/portable/linux/run.sh          # Linux x86_64
bash generator/portable/macos/run.sh --bw     # versão p&b
```

Para atualizar os binários embutidos (tarefa de dev, requer
`cargo`, `typst` e o cross-compiler musl):

```sh
bash generator/portable/update.sh
```

## Testes

A suíte roda três etapas: **format check** (limite de colunas),
**compile check** (todo header de `lib/` compila isolado) e os
**stress tests** de `tests/stress/`.

```sh
bash tests/run.sh
```

Durante a execução, aperte **`s`** para pular a etapa/teste em
curso (útil quando algum stress demora ou você só quer o resto).

### Ferramentas standalone

```sh
# checar o limite de 65 colunas (lib/ inteiro, um arquivo ou dir)
bash tests/check_format.sh
bash tests/check_format.sh lib/graphs/dijkstra.hpp
bash tests/check_format.sh -n 80 lib/          # limite custom

# só o compile-check dos headers
bash tests/compile_all.sh
```

## Convenções

- **65 colunas** por linha em `lib/` (validado pelo
  `check_format.sh`). Preferir nomes curtos (`l`/`r`, `ll` em
  vez de `long long`) para manter o código retangular.
- Cada header é auto-contido (`#include <bits/stdc++.h>` +
  aliases próprios), pronto para copiar e colar na prova.

## Requisitos

- **Testes:** `g++` (C++17).
- **PDF local:** `cargo` (Rust) e `typst`.
- **PDF portable:** nada além do repositório (binários embutidos).
