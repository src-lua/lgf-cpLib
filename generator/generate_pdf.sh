#!/bin/bash

set -e

echo "=== Compilando gerador LaTeX ==="
g++ -std=c++17 -o generate_latex generate_latex.cpp -O2 -lcrypto

echo "=== Gerando contents.tex ==="
./generate_latex

echo "=== Compilando PDF (1a passagem com XeLaTeX) ==="
xelatex -halt-on-error -file-line-error notebook.tex

echo "=== Compilando PDF (2a passagem com latexmk) ==="
latexmk -xelatex -f -silent notebook.tex

echo "=== Movendo PDF para diretório de saída ==="
mv notebook.pdf ../print/notebook.pdf

echo "=== Limpando arquivos temporários ==="
rm -f generate_latex
rm -f *.aux *.log *.out *.toc *.fdb_latexmk *.fls *.synctex.gz
rm -rf temp/

echo ""
echo "✅ PDF gerado com sucesso em ../print/notebook.pdf"
echo ""
echo "🦖 Good luck and good contest!"
echo ""
