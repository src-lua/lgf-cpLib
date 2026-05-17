// ── Metadata ─────────────────────────────────────────────────────────────────
#let university       = "Centro de Informática - UFPE"
#let university-short = "CIn - UFPE"
#let teamname         = "Lua | lgf-cplib"
#let authorname       = "Lua Guimarães Fernandes"

// ── Page setup ───────────────────────────────────────────────────────────────
// A4 landscape: 841.89 × 595.28 pt
#set page(
  width: 841.89pt,
  height: 595.28pt,
  margin: (left: 0.6cm, right: 1.3cm, top: 0.4cm, bottom: 0.4cm),
  header: none,
  footer: none,
)

// Vertical sidebar: team info top, page number bottom — in right margin
#let _sidebar_x = 841.89pt - 0.6cm - 0.65cm
#let _page_h    = 595.28pt
#set page(header: context {
  set text(size: 7pt, font: "JetBrains Mono")
  let info = box([#university | #authorname])
  let num  = box(width: 1cm, align(center)[*#counter(page).display()*])
  let si = measure(info)
  let sn = measure(num)
  let cx = _sidebar_x + si.height / 2
  place(top + left, dx: _sidebar_x, dy: 0.4cm,
    rotate(90deg, reflow: false, origin: top + left,
      box(width: _page_h, info)
    )
  )
  place(top + left, dx: cx - 0.5cm - 4pt, dy: _page_h - sn.height - 0.4cm,
    num
  )
})

// ── Fonts & base text ────────────────────────────────────────────────────────
#set text(font: "JetBrains Mono", size: 6.5pt, lang: "pt")
#set par(leading: 3pt, spacing: 3pt)

// ── Colors ───────────────────────────────────────────────────────────────────
#let _bw   = sys.inputs.at("bw", default: "false") == "true"
#let gray5 = if _bw { black } else { rgb("#6a737d") }

// ── Headings ─────────────────────────────────────────────────────────────────
#show heading.where(level: 1): it => {
  block(above: 5pt, below: 2pt)[
    #line(length: 100%, stroke: 0.5pt)
    #text(size: 8pt, weight: "bold")[#it.body]
    #line(length: 100%, stroke: 0.3pt)
  ]
}

#show heading.where(level: 2): it => {
  block(above: 5pt, below: 5pt)[
    #text(size: 7pt, weight: "semibold")[#it.body]
  ]
}

// ── Raw blocks ───────────────────────────────────────────────────────────────
#show raw.where(block: true): it => {
  set par(leading: 4.5pt, spacing: 0pt)
  set text(size: 5.5pt)
  it
}

// ── 3-column content ─────────────────────────────────────────────────────────
#columns(3, gutter: 6pt)[
  #align(center)[
    #text(size: 11pt, weight: "bold")[#teamname | #university-short]
    #v(3pt)
    #text(size: 6pt, fill: gray5)[#datetime.today().display("[day]/[month]/[year]")]
  ]

  #v(4pt)

  #outline(depth: 2, indent: 6pt)

  #v(4pt)

  #include "contents.typ"
]
