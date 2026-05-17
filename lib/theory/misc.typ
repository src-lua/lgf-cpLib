= Misc

== Floyd Cycle Detection

Dado $x_0$ e $f: S -> S$, detecta ciclo em $O(mu + lambda)$, $O(1)$ memoria.

1. $t=f(x_0)$, $h=f(f(x_0))$; avanca $t$ por 1, $h$ por 2 ate $t=h$.
2. $t=x_0$; avanca $t,h$ por 1 ate $t=h$: este e o inicio do ciclo ($mu$).
3. $t=h$; avanca $t$ por 1 ate $t=h$ novamente: este e o periodo ($lambda$).

== Bugs do Milênio

*Overflow:* `1LL<<40`, nao `1<<40`. `.size()` e `unsigned`. Intermediarios em `ll`.

*Doubles:* nunca `float`. Comparar com `EPS`. Cancelamento catastrofico. Nao dividir por zero.

*Modulo negativo:* `((x%n)+n)%n`.

*Grafos:* desconexo? Arestas negativas? Multi-arestas? Self-loops? Euler sem grau par?

*DP:* casos base cobertos? Indices na ordem certa? Limpou entre casos?

*I/O:* `ios::sync_with_stdio(false); cin.tie(NULL)`.
