= Teoria dos Números

== Euler Phi & Möbius

$phi(n)$: quantidade de inteiros em $[1,n]$ coprimos com $n$.

$ phi(n) = n product_(p | n) (1 - 1/p) = product_(i=1)^n p_i^(e_i - 1)(p_i - 1) $

$ phi(m n) = phi(m) phi(n) space (gcd=1), quad sum_(d | n) phi(d) = n $

$ a^(phi(m)) equiv 1 space (mod m) $

$ mu(n) = cases(1 & n=1, (-1)^r & n = p_1 dots.c p_r, 0 & p^2 | n) , quad sum_(d | n) mu(d) = [n=1] $

*Inversão de Möbius:* $g(n) = sum_(d|n) f(d) arrow.l.r.double f(n) = sum_(d|n) mu(n/d) g(d)$

$ 1/zeta(x) = sum_(i=1)^infinity mu(i)/i^x, quad (zeta(x-1))/(zeta(x)) = sum_(i=1)^infinity phi(i)/i^x, quad zeta^2(x) = sum_(i=1)^infinity d(i)/i^x $

== GCD, Diofantinas & TCR

$gcd(a,b) = gcd(b, a mod b)$; $"lcm"(a,b) = a b \/ gcd(a,b)$

*Bezout:* $a x + b y = gcd(a,b)$ sempre tem solução inteira. Em geral, $a x + b y = c$ tem solução $arrow.l.r.double gcd(a,b) | c$.

*TCR:* Sistema $x equiv a_i space (mod m_i)$ com $m_i$ coprimos dois a dois tem solucao unica $mod M = product m_i$:
$ x = sum_i a_i M_i (M_i^(-1) mod m_i), quad M_i = M/m_i $

== Aritmetica Modular

*Inverso modular:* $a^(-1) mod m$ via $a^(m-2) mod m$ (requer $m$ primo). Para todos os inversos $1 dots n$ de uma vez:
$ "inv"[1] = 1, quad "inv"[i] = -(m\/i) dot "inv"[m mod i] mod m $

*Lucas:* Para $p$ primo, $binom(n,k) mod p = binom(n mod p, k mod p) dot binom(floor(n/p), floor(k/p)) space (mod p)$
