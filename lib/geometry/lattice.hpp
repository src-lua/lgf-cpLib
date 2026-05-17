#pragma once

// Teorema de Pick: pontos inteiros interiores a um polígono.
// area2   = 2x a área com sinal (de area2())
// boundary = Σ gcd(|dx|, |dy|) sobre as arestas
long long lattice_points(long long area2, long long boundary) {
    return (area2 - boundary + 2) / 2;
}
