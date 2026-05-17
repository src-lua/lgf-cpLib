= Teoria dos Grafos

== Teoremas

*Euler:* Circuito Euleriano $arrow.l.r.double$ todos os vertices tem grau par. Caminho Euleriano $arrow.l.r.double$ exatamente 2 vertices de grau impar.

*Fórmula de Euler (planar):* $V - E + F = 2$. Grafo planar simples: $E <= 3V-6$; planar bipartido: $E <= 2V-4$. Todo planar tem algum vertice de grau $<= 5$.

*Cayley:* Número de árvores geradoras rotuladas de $K_n$ e $n^(n-2)$.

*Kirchhoff:* Número de árvores geradoras = qualquer cofator da matriz Laplaciana $L = D - A$.

*Konig:* Em grafo bipartido: cobertura mínima de vértices = emparelhamento máximo; conjunto independente máximo $= V -$ emparelhamento máximo.

*Hall:* Existe emparelhamento perfeito de $U$ $arrow.l.r.double$ $forall S subset.eq U: |N(S)| >= |S|$.

*Menger:* Número máximo de caminhos aresta-disjuntos entre $s$ e $t$ = tamanho do corte mínimo $s$-$t$.

*Dilworth:* Em poset, partição mínima em cadeias = anti-cadeia máxima.

*Mirsky:* Em poset, partição mínima em anti-cadeias = comprimento da maior cadeia.

*Prüfer:* Bijecao entre árvores rotuladas de $n$ vértices e sequências de comprimento $n-2$ sobre ${1,...,n}$.

*Erdos-Gallai:* Sequência $d_1 >= dots >= d_n$ é sequência de graus de algum grafo simples $arrow.l.r.double$ $sum d_i$ e par e para todo $k$:
$ sum_(i=1)^k d_i <= k(k-1) + sum_(i=k+1)^n min(d_i, k) $

== Tipos de Grafo

#align(center, image("graphs.png", width: 80%))
