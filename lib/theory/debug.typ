= Debugging

```bash
-g++ -O2 -std=c++17 -Wall -Wextra
    -fsanitize=address,undefined
    -fno-sanitize-recover=all -g
```

*Antes de submeter:*
- Escreva casos simples se o sample não for suficiente.
- Limite de tempo apertado? Gere casos máximos.
- Memória está ok?
- Algo pode dar overflow?
- Está submetendo o arquivo certo?

*Wrong Answer:*
- Imprima sua solução e outputs de debug.
- Está limpando estruturas entre casos de teste?
- O algoritmo cobre todo o range de entrada?
- Releia o enunciado completo.
- Todos os casos de borda estão corretos?
- Entendeu o problema corretamente?
- Variáveis não inicializadas?
- Overflow?
- Confundindo N/M, i/j, etc.?
- Tem certeza que o algoritmo funciona?
- Que casos especiais você não considerou?
- As funções da STL funcionam como você acha?
- Adicione `assert`s e ressubmeta.
- Rode em casos criados manualmente.
- Execute o algoritmo num caso simples à mão.
- Explique o algoritmo para um colega.
- Peça para o colega revisar seu código.
- Dê uma volta, vá ao banheiro.
- O formato de saída está correto? (espaços, newlines)
- Reescreva do zero ou peça ao colega.

*Runtime Error:*
- Testou todos os casos de borda localmente?
- Variáveis não inicializadas?
- Lendo/escrevendo fora do range de algum vetor?
- Algum `assert` que pode falhar?
- Divisão por zero? (`mod 0`?)
- Recursão infinita possível?
- Ponteiros ou iteradores invalidados?
- Usando memória demais?

*Time Limit Exceeded:*
- Tem loop infinito?
- Qual é a complexidade do algoritmo?
- Está copiando dados desnecessariamente? (use referências)
- Tamanho da entrada/saída? (considere `scanf`)
- Evite `map`/`vector`; use arrays/`unordered_map`.
- O que seus colegas acham do algoritmo?

*Memory Limit Exceeded:*
- Quanto de memória seu algoritmo realmente precisa?
- Está limpando estruturas entre casos de teste?
