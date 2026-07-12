= Tabelas de Referência

== Tipos, Constantes & Complexidade

#set text(size: 6pt)

#grid(
  columns: (auto, 1fr),
  gutter: 6pt,
  [
    #table(
      columns: 4,
      stroke: 0.3pt,
      inset: 3pt,
      [type],[bits],[max],[fmt],
      [`int`],[32],[$approx 2.1 times 10^9$],[`%d`],
      [`uint`],[32],[$approx 4.3 times 10^9$],[`%u`],
      [`ll`],[64],[$approx 9.2 times 10^(18)$],[`%lld`],
      [`ull`],[64],[$approx 1.8 times 10^(19)$],[`%llu`],
      [`double`],[64],[$10^(308)$, $epsilon approx 10^(-15)$],[`%lf`],
      [`long dbl`],[80],[$10^(4932)$, $epsilon approx 10^(-18)$],[`%Lf`],
    )

    #v(4pt)

    #grid(
      columns: (auto, auto),
      gutter: 4pt,
      table(
        columns: 2,
        stroke: 0.3pt,
        inset: 3pt,
        [$n$], [$pi(n)$],
        [$10^4$],[1229],
        [$10^5$],[9592],
        [$10^6$],[78498],
        [$10^7$],[664579],
        [$10^8$],[5761455],
        [$10^9$],[50847534],
      ),
      table(
        columns: 2,
        stroke: 0.3pt,
        inset: 3pt,
        [$n$],[$O$ viavel],
        [$10^8$],[$O(n)$],
        [$10^7$],[$O(n log n)$],
        [$5 times 10^3$],[$O(n^2)$],
        [$500$],[$O(n^3)$],
        [$22$],[$O(2^n n)$],
        [$11$],[$O(n!)$],
      ),
    )
  ],
  [
    #table(
      columns: 2,
      stroke: 0.3pt,
      inset: 3pt,
      [valor],[obs],
      [$12! = 479001600$],[`int`],
      [$20! approx 2.4 times 10^(18)$],[`ll`],
      [$binom(33,16) approx 1.2 times 10^9$],[`int`],
      [$binom(66,33) approx 7.2 times 10^(18)$],[`ll`],
    )

    #v(4pt)

    #table(
      columns: 2,
      stroke: 0.3pt,
      inset: 3pt,
      table.header(table.cell(colspan: 2)[$2^(-1) mod p$]),
      [$10^9+7$],[`500000004`],
      [$10^9+9$],[`500000005`],
      [$998244353$],[`499122177`],
      [$2^(61)-1$],[`1152921504606846976`],
    )
  ],
)
