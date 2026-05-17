// Stirling number helpers
#let stir1(n, k) = $lr([vec(delim: #none, #n, #k)])$
#let stir2(n, k) = $lr({vec(delim: #none, #n, #k)})$
#let euler1(n, k) = $lr(chevron.l vec(delim: #none, #n, #k) chevron.r)$

= Combinatória

== Somatórios

$ sum_(i=1)^n i = n(n+1)/2, quad sum_(i=1)^n i^2 = (n(n+1)(2n+1))/6, quad sum_(i=1)^n i^3 = n^2(n+1)^2/4 $

$ sum_(i=1)^n i^m = 1/(m+1) sum_(k=0)^m binom(m+1, k) B_k n^(m+1-k) $

$ sum_(i=0)^n c^i = (c^(n+1)-1)/(c-1), quad sum_(i=0)^infinity c^i = 1/(1-c), quad |c|<1 $

$ sum_(i=0)^n i c^i = (n c^(n+2) - (n+1) c^(n+1) + c) / (c-1)^2, quad sum_(i=0)^infinity i c^i = c/(1-c)^2, quad |c|<1 $

$ H_n = sum_(i=1)^n 1/i approx ln n + 0.5772, quad ln n < H_n < ln n + 1 $

$ sum_(i=1)^n H_i = (n+1) H_n - n, quad sum_(i=1)^n i H_i = (n(n+1))/2 H_n - (n(n-1))/4 $

== Identidades Binomiais

$ binom(n,k) = n! / ((n-k)! k!) = binom(n, n-k) = n/k binom(n-1, k-1) = binom(n-1,k) + binom(n-1,k-1) $

$ binom(n,m) binom(m,k) = binom(n,k) binom(n-k,m-k), quad binom(n,k) = (-1)^k binom(k-n-1, k) $

$ (x+y)^n = sum_(k=0)^n binom(n,k) x^(n-k) y^k, quad x^n - y^n = (x-y) sum_(k=0)^(n-1) x^(n-1-k) y^k $

$ sum_(k=0)^n binom(n,k) = 2^n, quad sum_(k=0)^n (-1)^k binom(n,k) = 0 $

$ sum_(k=0)^n k binom(n,k) = n 2^(n-1), quad sum_(k=0)^n k^2 binom(n,k) = n(n+1) 2^(n-2) $

$ sum_(k=0)^n binom(r+k, k) = binom(r+n+1, n), quad sum_(k=0)^n binom(k,m) = binom(n+1, m+1) $

$ sum_(k=0)^n binom(r,k) binom(s, n-k) = binom(r+s, n), quad sum_(k=0)^n binom(n,k)^2 = binom(2n,n) $

$ sum_(k=0)^r (-1)^k binom(n,k) = (-1)^r binom(n-1,r) $

$ (1+x)^n = sum_(k=0)^n binom(n,k) x^k, quad (1+x)^(-n) = sum_(k=0)^infinity (-1)^k binom(n+k-1, k) x^k $

#v(4pt) 

*Inversao binomial:*
$f(n) = sum_k binom(n,k) g(k) arrow.l.r.double g(n) = sum_k (-1)^(n-k) binom(n,k) f(k)$

#colbreak()

== Contagem

*Permutacoes* com repeticoes $n_1, dots, n_r$: $n! / (n_1! dots.c n_r!)$

*Permutacoes circulares:* $(n-1)!$

*Stars & Bars:* $x_1 + dots.c + x_k = n$, $x_i >= 0$: $binom(n+k-1, k-1)$

*Inclusao-Exclusao:*
$|union.big_(i=1)^n A_i| = sum|A_i| - sum|A_i inter A_j| + dots.c plus.minus |A_1 inter dots.c inter A_n|$

== Sequências Especiais

*Catalan:* $C_n = 1/(n+1) binom(2n,n)$; $1,1,2,5,14,42,132,429,dots$

Conta: arvores binarias com $n$ nos, triangulacoes de $(n+2)$-gono, $n$ pares de parenteses validos.

#v(4pt)
*Fibonacci:* $F_0=F_1=1$, $F_(-i) = (-1)^(i-1) F_i$

$ F_n = (phi^n - psi^n) / sqrt(5), quad phi = (1+sqrt(5))/2, quad psi = (1-sqrt(5))/2 $

$ F_(i+1) F_(i-1) - F_i^2 = (-1)^i quad ("Cassini") $

$ F_(n+k) = F_k F_(n+1) + F_(k-1) F_n, quad F_(2n) = F_n F_(n+1) + F_(n-1) F_n $

$ gcd(F_m, F_n) = F_(gcd(m,n)), quad sum_(k=1)^n F_k = F_(n+2) - 1, quad sum_(k=1)^n F_k^2 = F_n F_(n+1) $

$ mat(F_n, F_(n-1); F_(n-1), F_(n-2)) = mat(1,1; 1,0)^n $

Representacao de Fibonacci: todo $n$ tem representacao unica $n = F_(k_1) + dots.c + F_(k_m)$, $k_i >= k_(i+1)+2$, $k_m >= 2$.

#v(4pt)
*Stirling 1ª especie* #stir1($n$,$k$): permutacoes de $n$ com $k$ ciclos.

$ #stir1($n$,$1$) = (n-1)!, quad #stir1($n$,$2$) = (n-1)! H_(n-1), quad #stir1($n$,$n$) = 1 $

$ #stir1($n$,$k$) = (n-1) #stir1($n-1$,$k$) + #stir1($n-1$,$k-1$), quad sum_k #stir1($n$,$k$) = n! $

$ x^overline(n) = sum_(k=0)^n #stir1($n$,$k$) x^k, quad #stir1($n$,$n-1$) = binom(n,2) $

#v(4pt)
*Stirling 2ª especie* #stir2($n$,$k$): particoes de $n$ em $k$ subconjuntos nao vazios.

$ #stir2($n$,$1$) = #stir2($n$,$n$) = 1, quad #stir2($n$,$2$) = 2^(n-1)-1, quad #stir2($n$,$n-1$) = #stir1($n$,$n-1$) = binom(n,2) $

$ #stir2($n$,$k$) = k #stir2($n-1$,$k$) + #stir2($n-1$,$k-1$) = 1/k! sum_(j=0)^k (-1)^(k-j) binom(k,j) j^n $

#v(4pt)
*Bell* $B_n = sum_k #stir2($n$,$k$)$: \# particoes de ${1,...,n}$ em subconjuntos nao vazios.

$B_0=1, B_1=1, B_2=2, B_3=5, B_4=15, B_5=52, B_6=203$

#v(4pt)
*Numeros de Euler* #euler1($n$,$k$): permutacoes de $n$ com $k$ ascendentes.

$ #euler1($n$,$0$) = #euler1($n$,$n-1$) = 1, quad #euler1($n$,$k$) = #euler1($n$,$n-1-k$), quad #euler1($n$,$k$) = (k+1) #euler1($n-1$,$k$) + (n-k) #euler1($n-1$,$k-1$) $

$ #euler1($n$,$1$) = 2^n - n - 1, quad #euler1($n$,$m$) = sum_(k=0)^m (-1)^k binom(n+1, k) (m+1-k)^n $

$ x^n = sum_(k=0)^n #euler1($n$,$k$) binom(x+k, n) $

#v(4pt)
*Derangements:* $D_n = (n-1)(D_(n-1) + D_(n-2))$; $D_n approx n!/e$

#v(4pt)
*Josephus:* $f(1,k)=0$, $f(n,k) = (f(n-1,k)+k) mod n$

== Funções Geradoras

Serie ordinaria: $A(x) = sum_(i>=0) a_i x^i$; exponencial: $A(x) = sum_(i>=0) a_i x^i / i!$

$ 1/(1-x) = sum x^i, quad e^x = sum x^i / i!, quad ln(1+x) = sum (-1)^(i+1) x^i / i $

$ (1+x)^n = sum binom(n,i) x^i, quad x/(1-x-x^2) = sum F_i x^i $

$ 1/(2x) lr((1 - sqrt(1-4x))) = sum C_i x^i, quad 1/sqrt(1-4x) = sum binom(2i,i) x^i $

*Convolucao:* $A(x) B(x) = sum_i (sum_(j=0)^i a_j b_(i-j)) x^i$.

*Soma acumulada:* $B(x) = 1/(1-x) A(x)$ se $b_i = sum_(j<=i) a_j$.

== Potências Fatoriais & Bernoulli

$ x^underline(n) = x(x-1) dots.c (x-n+1), quad x^overline(n) = x(x+1) dots.c (x+n-1) $

$ x^underline(n) = sum_(k=1)^n #stir1($n$,$k$) (-1)^(n-k) x^k, quad x^overline(n) = sum_(k=1)^n #stir1($n$,$k$) x^k $

$ x^n = sum_(k=1)^n #stir2($n$,$k$) x^underline(k) $

*Numeros de Bernoulli* ($B_i=0$ para $i$ impar $>1$):

$B_0=1$, $B_1=-1/2$, $B_2=1/6$, $B_4=-1/30$, $B_6=1/42$, $B_8=-1/30$

$ x/(e^x-1) = sum_(i>=0) B_i x^i / i!, quad n! = sqrt(2 pi n) (n/e)^n (1 + Theta(1/n)) $

