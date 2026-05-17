= Matemática

== Probabilidade

*Bayes:* Atualiza a probabilidade de $A$ dado que $B$ ocorreu.
$ P(A|B) = (P(B|A) P(A)) / P(B) $
Quando $P(B)$ nao e conhecida diretamente ($A_j$ sao hipoteses mutuamente exclusivas e exaustivas):
$ P(A_i|B) = (P(B|A_i) P(A_i)) / (sum_j P(B|A_j) P(A_j)) $

*Esperanca:* $E[X] = sum x P(X=x)$

Linearidade: $E[a X + b Y] = a E[X] + b E[Y]$. Se independentes: $E[X Y] = E[X] E[Y]$

*Variancia:* $"Var"(X) = E[X^2] - E[X]^2$; $"Var"(a X+b) = a^2 "Var"(X)$

Se independentes: $"Var"(X+Y) = "Var"(X) + "Var"(Y)$

*Markov:* $P[X >= lambda E[X]] <= 1/lambda$

*Chebyshev:* $P[|X - E[X]| >= lambda sigma] <= 1/lambda^2$

#line(length: 100%, stroke: 0.2pt)

*Binomial* $B(n,p)$: $n$ ensaios de Bernoulli independentes com prob $p$.
$ P(X=k) = binom(n,k) p^k (1-p)^(n-k), quad E[X]=n p, quad "Var"=n p(1-p) $

#line(length: 100%, stroke: 0.2pt)

*Geometrica* $"Geom"(p)$: numero de tentativas ate o primeiro sucesso ($q=1-p$).
$ P(X=k) = p q^(k-1), quad E[X] = 1/p, quad "Var" = q/p^2 $

#line(length: 100%, stroke: 0.2pt)

*Hipergeometrica* $H(N,K,n)$: $N$ itens, $K$ marcados, $n$ sorteados sem reposicao.
$ P(X=k) = binom(K,k) binom(N-K, n-k) / binom(N,n), quad E[X] = (n K)/N $

#line(length: 100%, stroke: 0.2pt)

*Poisson* $"Pois"(lambda)$: aproximacao de $B(n,p)$ quando $n->infinity$, $n p = lambda$.
$ P(X=k) = (e^(-lambda) lambda^k) / k!, quad E[X] = "Var"(X) = lambda $

#line(length: 100%, stroke: 0.2pt)

*Normal* $cal(N)(mu, sigma^2)$: $p(x) = 1/(sqrt(2pi) sigma) e^(-(x-mu)^2 \/ 2sigma^2)$, $E[X]=mu$, $"Var"=sigma^2$.

#line(length: 100%, stroke: 0.2pt)

*Coupon collector:* $n$ tipos equiprovaveis; numero esperado de sorteios $= n H_n$.

*Paradoxo do aniversario:* $approx 1.18 sqrt(M)$ amostras de $[M]$ para colisao com prob $>= 50%$.

== Trigonometria

$sin^2 x + cos^2 x = 1$, $1 + tan^2 x = sec^2 x$, $1 + cot^2 x = csc^2 x$

$sin(x plus.minus y) = sin x cos y plus.minus cos x sin y$

$cos(x plus.minus y) = cos x cos y minus.plus sin x sin y$

$tan(x plus.minus y) = (tan x plus.minus tan y) / (1 minus.plus tan x tan y)$

$sin 2x = 2 sin x cos x$, $cos 2x = cos^2 x - sin^2 x = 2cos^2 x - 1 = 1 - 2sin^2 x$

$e^(i x) = cos x + i sin x$, $e^(i pi) = -1$

*Lei dos senos:* $a / sin A = b / sin B = c / sin C = 2R$

*Lei dos cossenos:* $c^2 = a^2 + b^2 - 2a b cos C$

*Area do triangulo (lados a,b,c; angulos A,B,C):*
$ 1/2 a b sin C, quad sqrt(s(s-a)(s-b)(s-c)) space s=(a+b+c)/2, quad (c^2 sin A sin B)/(2 sin C) $

*Circumraio:* $R = a b c / (4A)$. *Inraio:* $r = A/s$.

== Geometria

*Shoelace:* $A = 1/2 |sum_i (x_i y_(i+1) - x_(i+1) y_i)|$

*Pick:* $A = I + B/2 - 1$ ($I$ = pontos interiores, $B$ = pontos na borda)

*Area por coordenadas:* $1/2 |det mat(x_1-x_3, x_2-x_3; y_1-y_3, y_2-y_3)|$

*Esferas/circulos:* $A = pi r^2$, $V = 4/3 pi r^3$.

*Produto vetorial:* $arrow(u) times arrow(v) = (u_y v_z - u_z v_y, space u_z v_x - u_x v_z, space u_x v_y - u_y v_x)$

Em 2D: $u_x v_y - u_y v_x$ ($>0$ anti-horario, $=0$ colinear; modulo = area do paralelogramo)

*Dist. ponto-ponto:* $d = sqrt((x_1-x_2)^2 + (y_1-y_2)^2)$ (3D: inclui $(z_1-z_2)^2$)

*Dist. ponto-reta* ($a x + b y + c = 0$): $d = |a x_0 + b y_0 + c| / sqrt(a^2 + b^2)$

*Rotacao 2D:*
$ mat(x'; y') = mat(cos theta, -sin theta; sin theta, cos theta) mat(x; y) $

*Rotacao 3D* em torno de $x$, $y$, $z$ por $theta$ ($c=cos theta$, $s=sin theta$):
$ R_x = mat(1,0,0; 0,c,-s; 0,s,c), quad R_y = mat(c,0,s; 0,1,0; -s,0,c), quad R_z = mat(c,-s,0; s,c,0; 0,0,1) $
