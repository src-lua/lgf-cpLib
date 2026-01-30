# Gerador de PDF - Ex-usuários de Python

Sistema avançado de geração de PDF para competitive programming, baseado no [repositório do SamuellH12](https://github.com/SamuellH12/Competitive-Programming-Algorithms).

## ✨ Features

- ✅ **Hash MD5**: Cada código tem um hash para verificação durante contests
- ✅ **Filtros inteligentes**: Remove automaticamente linhas de debug/testes
- ✅ **Ferramenta de verificação**: Valida código copiado do PDF
- ⚠️ **Descrições inline**: Suporte preparado (desativado por padrão)

---

## 📦 Dependências

### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install -y \
    g++ \
    libssl-dev \
    texlive-latex-base \
    texlive-latex-extra \
    latexmk \
    python3
```

### Verificar instalação

```bash
g++ --version          # Compilador C++
pdflatex --version     # LaTeX
latexmk --version      # Automação LaTeX
python3 --version      # Python
```

---

## 🚀 Uso

### 1. Gerar PDF

```bash
cd generator/

# Opção 1: Gerar contents.txt automaticamente
python3 getContents.py > contents.txt

# Opção 2: Editar contents.txt manualmente
# - Comentar com # arquivos que não quer incluir
# - Reordenar seções
# - Ajustar nomes

# Gerar PDF
./generate_pdf.sh

# PDF gerado em: ../print/notebook.pdf
```

### 2. Verificar Hash (durante contest)

```bash
cd generator/hash/
./compile_and_run.sh

# Cole o código copiado do PDF quando solicitado
# O programa mostrará o hash MD5 calculado
# Compare com o hash exibido no PDF
```

---

## 📁 Estrutura

```
generator/
├── generate_latex.cpp      # Processador principal (C++)
├── generate_pdf.sh         # Script de build
├── getContents.py          # Gerador automático de contents.txt
├── contents.txt            # Lista de arquivos a incluir
├── notebook.tex            # Template LaTeX
├── hash/
│   ├── md5hsh.cpp         # Implementação MD5
│   └── compile_and_run.sh # Helper de compilação
└── README.md              # Este arquivo
```

---

## ⚙️ Configurações

### Desabilitar Hash

Edite `generate_latex.cpp`:

```cpp
const bool USE_HASH = false;  // Linha 6
```

### Ativar Descrições

Edite `generate_latex.cpp`:

```cpp
const bool ADD_DESC = true;    // Linha 33
const bool BLOCK_DESC = true;  // Linha 37
```

Depois adicione descrições no código:

```cpp
/*LATEX_DESC_BEGIN
**Fenwick Tree (BIT)**

Complexidade:
- Update: O(log n)
- Query: O(log n)
LATEX_DESC_END*/

template<typename T>
struct fenwick_tree {
    // implementação...
};
```

### Ajustar Número de Colunas

Edite `notebook.tex` linha 175:

```latex
\begin{multicols}{3}  % Mude para 2 ou 4 conforme preferência
```

---

## 🔧 Marcadores de Filtragem

### Remover Linhas Específicas

```cpp
// DEBUG
cout << "teste" << endl;  // ← removido do PDF
```

### Remover Blocos

```cpp
// LATEX_IGNORED_BEGIN
void test_function() {
    // código de teste - não aparece no PDF
}
// LATEX_IGNORED_END
```

### Desabilitar Hash para Arquivo Específico

Em `contents.txt`, adicione `@` no final do nome:

```
../lgf-cplib/examples/tags.hpp $ Tags @
```

---

## 🐛 Troubleshooting

### Erro: "openssl/md5.h: No such file or directory"

Instale: `sudo apt-get install libssl-dev`

### Erro: "pdflatex: command not found"

Instale: `sudo apt-get install texlive-latex-base texlive-latex-extra`

### Erro: "latexmk: command not found"

Instale: `sudo apt-get install latexmk`

### PDF não gerado

1. Verifique se `../print/` existe: `mkdir -p ../print`
2. Veja logs de erro do pdflatex
3. Teste compilação manual: `pdflatex notebook.tex`

---

## 📝 Workflow Recomendado

1. **Desenvolver código** em `/lgf-cplib/`
2. **Testar** código funciona
3. **Gerar contents.txt**: `python3 getContents.py > contents.txt`
4. **Revisar** `contents.txt` (comentar arquivos indesejados)
5. **Gerar PDF**: `./generate_pdf.sh`
6. **Imprimir** PDF para contest
7. **Durante contest**: usar `hash/compile_and_run.sh` para validar código

---

## 🎯 Próximos Passos (Opcional)

- [ ] Ativar descrições inline (`ADD_DESC = true`)
- [ ] Adicionar cheat sheets em `extra/`
- [ ] Configurar CI/CD para gerar PDF automaticamente
- [ ] Adicionar mais filtros personalizados

---

## 📚 Créditos

- Sistema original: [SamuellH12](https://github.com/SamuellH12/Competitive-Programming-Algorithms)
- Adaptação: Ex-usuários de Python | CIn - UFPE
