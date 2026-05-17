= Recorrências & Séries

== Teorema Mestre

$T(n) = a T(n/b) + f(n)$, $a >= 1$, $b > 1$:

$f(n) = O(n^(log_b a - epsilon)) => T(n) = Theta(n^(log_b a))$

$f(n) = Theta(n^(log_b a)) => T(n) = Theta(n^(log_b a) log n)$

$f(n) = Omega(n^(log_b a + epsilon))$ e $a f(n/b) <= c f(n) => T(n) = Theta(f(n))$

== Séries de Taylor

$ e^x = sum x^i / i!, quad ln(1+x) = sum (-1)^(i+1) x^i / i, quad ln 1/(1-x) = sum x^i / i $

$ sin x = sum (-1)^i x^(2i+1) / (2i+1)!, quad cos x = sum (-1)^i x^(2i) / (2i)! $

$ arctan x = sum (-1)^i x^(2i+1) / (2i+1), quad 1/(1-x)^(n+1) = sum binom(i+n, i) x^i $
