= Teoria dos Jogos

*Sprague-Grundy:* Todo jogo imparcial equivale a um Nim de um unico monte. O valor de Grundy (nimber) de uma posicao $u$ e:
$ g(u) = "mex"{g(v) : v " alcançável de " u} $
onde $"mex"(S)$ e o menor inteiro nao negativo fora de $S$.

Posição perdedora $arrow.l.r.double$ $g(u)=0$. Em jogo composto de partes independentes:
$ g = g_1 xor g_2 xor dots.c xor g_k $

*Nim:* $k$ montes de tamanhos $a_1, dots, a_k$. Posição perdedora $arrow.l.r.double$ $a_1 xor dots.c xor a_k = 0$.

*Nim misere* (quem pegar o ultimo _perde_): subtraia 1 de cada pilha; se o XOR resultante $eq.not 0$, a posicao original e ganhadora.

*Wythoff:* 2 montes $(a,b)$, $a <= b$. Movimentos: remover qualquer qtd de um monte, ou a mesma qtd dos dois. Posição perdedora $arrow.l.r.double$ $a = floor(phi k)$, $b = floor(phi^2 k)$ para algum $k >= 0$, onde $phi = (1+sqrt(5))/2$.
