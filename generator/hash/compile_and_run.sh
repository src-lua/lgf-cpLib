#!/bin/bash

echo "=== Compilando ferramenta de verificação de hash ==="
g++ -std=c++17 -o md5tool md5hsh.cpp -O2 -lcrypto

if [ $? -eq 0 ]; then
    echo "✅ Compilação bem-sucedida!"
    echo ""
    echo "=== Executando ferramenta de hash ==="
    echo "Cole o código copiado do PDF abaixo (Ctrl+D para finalizar):"
    echo ""
    ./md5tool
else
    echo "❌ Erro na compilação!"
    exit 1
fi
